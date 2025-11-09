#include <stdio.h>
#include <math.h>

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    printf("Newton's Rings - Simulator / Calculator\n");
    printf("Formulas referenced from lab handout (Newton's Ring experiment).\n\n");

    while (1) {
        printf("Choose an option:\n");
        printf("1) Compute wavelength (λ) from measured diameters Dn and Dn+p\n");
        printf("2) Compute radius (Rn) or diameter (Dn) of nth bright ring\n");
        printf("3) Exit\n");
        printf("Enter choice (1-3): ");
        int choice;
        if (scanf("%d", &choice) != 1) { clear_stdin(); printf("Invalid input.\n\n"); continue; }

        if (choice == 1) {
            /* wavelength calculation */
            double Dn, Dnp;   /* diameters in meters */
            double R;         /* radius of curvature in meters */
            int n, p;
            double mu;

            printf("\n-- Compute wavelength from measured diameters --\n");
            printf("Enter diameter Dn (in mm): ");
            if (scanf("%lf", &Dn) != 1) { clear_stdin(); printf("Invalid.\n\n"); continue; }
            printf("Enter diameter Dn+p (in mm): ");
            if (scanf("%lf", &Dnp) != 1) { clear_stdin(); printf("Invalid.\n\n"); continue; }
            printf("Enter order number n (integer, e.g. 1): ");
            if (scanf("%d", &n) != 1) { clear_stdin(); printf("Invalid.\n\n"); continue; }
            printf("Enter p (difference in orders, integer > 0, e.g. 1,2...): ");
            if (scanf("%d", &p) != 1 || p <= 0) { clear_stdin(); printf("Invalid p.\n\n"); continue; }
            printf("Enter radius of curvature R (in mm): ");
            if (scanf("%lf", &R) != 1 || R <= 0) { clear_stdin(); printf("Invalid R.\n\n"); continue; }
            printf("Enter refractive index of medium mu (e.g. air=1.0): ");
            if (scanf("%lf", &mu) != 1 || mu <= 0) { clear_stdin(); printf("Invalid mu.\n\n"); continue; }

            /* convert mm -> m for SI */
            double Dn_m = Dn / 1000.0;
            double Dnp_m = Dnp / 1000.0;
            double R_m = R / 1000.0;12
            

            /* formula from lab: lambda_medium = (D_{n+p}^2 - D_n^2) / (4 * p * R)
               then lambda_vacuum = mu * lambda_medium  (if medium refractive index mu used) */
            double numerator = (Dnp_m * Dnp_m) - (Dn_m * Dn_m);
            if (numerator <= 0.0) {
                printf("Error: (D_{n+p}^2 - D_n^2) must be positive. Check inputs.\n\n");
                continue;
            }
            double lambda_medium = numerator / (4.0 * p * R_m);
            double lambda_vacuum = mu * lambda_medium;

            printf("\nResults:\n");
            printf("Wavelength in medium (lambda_medium) = %.6e m = %.3f nm\n", lambda_medium, lambda_medium * 1e9);
            printf("Wavelength in vacuum/air (lambda_vacuum = mu * lambda_medium) = %.6e m = %.3f nm\n",
                   lambda_vacuum, lambda_vacuum * 1e9);
            printf("Also: in Angstroms: medium = %.3f A, vacuum = %.3f A\n\n",
                   lambda_medium * 1e10, lambda_vacuum * 1e10);
        }
        else if (choice == 2) {
            double R;       /* in mm or m but keep consistent with input */
            printf("\n-- Compute radius (rn) / diameter (Dn) of nth bright ring --\n");
            printf("You can provide wavelength as vacuum value or in-medium.\n");
            printf("Enter '1' to input wavelength in vacuum (lambda_vacuum), '2' for in-medium (lambda_medium): ");
            int wchoice;
            if (scanf("%d", &wchoice) != 1) { clear_stdin(); printf("Invalid.\n\n"); continue; }

            double lambda_vac, lambda_med;
            double mu;
            if (wchoice == 1) {
                printf("Enter vacuum wavelength lambda_vacuum (in nm): ");
                if (scanf("%lf", &lambda_vac) != 1) { clear_stdin(); printf("Invalid.\n\n"); continue; }
                printf("Enter refractive index of medium mu (e.g. air=1.0): ");
                if (scanf("%lf", &mu) != 1 || mu <= 0) { clear_stdin(); printf("Invalid mu.\n\n"); continue; }
                lambda_med = (lambda_vac * 1e-9) / mu; /* convert nm -> m and in-medium */
            } else if (wchoice == 2) {
                printf("Enter in-medium wavelength lambda_medium (in nm): ");
                if (scanf("%lf", &lambda_med) != 1) { clear_stdin(); printf("Invalid.\n\n"); continue; }
                lambda_med = lambda_med * 1e-9; /* to meters */
                /* will not compute vacuum lambda unless user asks */
                mu = -1.0;
            } else {
                clear_stdin(); printf("Invalid choice.\n\n"); continue;
            }

            printf("Enter lens radius of curvature R (in mm): ");
            if (scanf("%lf", &R) != 1 || R <= 0) { clear_stdin(); printf("Invalid R.\n\n"); continue; }
            printf("Enter order number n (integer >= 1): ");
            int n;
            if (scanf("%d", &n) != 1 || n < 1) { clear_stdin(); printf("Invalid n.\n\n"); continue; }

            /* convert R mm -> m */
            double R_m = R / 1000.0;

            /* formula: r_n = sqrt( ((2n-1) * lambda_medium * R) / 2 )  */
            double inside = ((2.0 * n - 1.0) * lambda_med * R_m) / 2.0;
            if (inside < 0.0) {
                printf("Computation error (negative inside sqrt). Check inputs.\n\n");
                continue;
            }
            double rn = sqrt(inside); /* meters */
            double Dn = 2.0 * rn;

            printf("\nResults (using lambda_medium = %.6e m):\n", lambda_med);
            printf("Radius of nth bright ring r_%d = %.6e m = %.3f mm\n", n, rn, rn * 1e3);
            printf("Diameter D_%d = %.6e m = %.3f mm\n", n, Dn, Dn * 1e3);
            if (mu > 0) {
                double lambda_vac_calc = lambda_med * mu;
                printf("Corresponding vacuum wavelength (lambda_vacuum = mu * lambda_medium) = %.3f nm\n\n",
                       lambda_vac_calc * 1e9);
            } else {
                printf("\n");
            }
        }
        else if (choice == 3) {
            printf("Exiting.\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
