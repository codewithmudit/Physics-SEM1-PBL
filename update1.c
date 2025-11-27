#include <stdio.h>
#include <math.h>

// Utility functions
void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

double to_angstrom(double lambda_m) {
    return lambda_m * 1e10;
}

void header(const char *title) {
    printf("\n**\n");
    printf("* %s\n", title);
    printf("\n\n");
}

// Function for Choice 1: Compute wavelength from diameters
void compute_wavelength() {
    header("Compute Wavelength from Diameters");

    double Dn, Dnp, R, mu;
    int n, p;

    printf("Enter diameter Dn (mm): ");
    if (scanf("%lf", &Dn) != 1) { 
        clear_stdin(); 
        printf("Invalid input.\n");
        return; 
    }

    printf("Enter diameter Dn+p (mm): ");
    if (scanf("%lf", &Dnp) != 1) { 
        clear_stdin(); 
        printf("Invalid input.\n");
        return; 
    }

    printf("Enter order n: ");
    if (scanf("%d", &n) != 1) { 
        clear_stdin(); 
        printf("Invalid input.\n");
        return; 
    }

    printf("Enter p (>0): ");
    if (scanf("%d", &p) != 1 || p <= 0) { 
        clear_stdin(); 
        printf("Invalid input. p must be > 0.\n");
        return; 
    }

    printf("Enter radius of curvature R (mm): ");
    if (scanf("%lf", &R) != 1 || R <= 0) { 
        clear_stdin(); 
        printf("Invalid input. R must be > 0.\n");
        return; 
    }

    printf("Enter refractive index mu: ");
    if (scanf("%lf", &mu) != 1 || mu <= 0) { 
        clear_stdin(); 
        printf("Invalid input. mu must be > 0.\n");
        return; 
    }

    // Convert to meters
    double Dn_m = Dn / 1000.0;
    double Dnp_m = Dnp / 1000.0;
    double R_m = R / 1000.0;

    double numerator = (Dnp_m * Dnp_m) - (Dn_m * Dn_m);
    if (numerator <= 0) {
        printf("Error: D(n+p)^2 must be > D(n)^2.\n");
        return;
    }

    double lambda_med = numerator / (4.0 * p * R_m);
    double lambda_vac = mu * lambda_med;

    printf("--------------------------------------------------\n");
    printf(" Results (Now also in Angstroms)\n");
    printf("--------------------------------------------------\n");
    printf("Lambda (medium): %.6e m  | %.3f A\n", lambda_med, to_angstrom(lambda_med));
    printf("Lambda (vacuum): %.6e m  | %.3f A\n\n", lambda_vac, to_angstrom(lambda_vac));
}

// Function for Choice 2: Compute bright ring
void compute_bright_ring() {
    header("Bright Ring Calculator");

    int wchoice;
    printf("Enter 1 for lambda_vacuum (nm), 2 for lambda_medium (nm): ");
    if (scanf("%d", &wchoice) != 1) { 
        clear_stdin(); 
        printf("Invalid input.\n");
        return; 
    }

    double lambda_vac, lambda_med, mu;

    if (wchoice == 1) {
        printf("Enter lambda_vacuum (nm): ");
        if (scanf("%lf", &lambda_vac) != 1) {
            clear_stdin();
            printf("Invalid input.\n");
            return;
        }
        printf("Enter refractive index mu: ");
        if (scanf("%lf", &mu) != 1) {
            clear_stdin();
            printf("Invalid input.\n");
            return;
        }
        lambda_med = (lambda_vac * 1e-9) / mu;
    } else if (wchoice == 2) {
        printf("Enter lambda_medium (nm): ");
        if (scanf("%lf", &lambda_med) != 1) {
            clear_stdin();
            printf("Invalid input.\n");
            return;
        }
        lambda_med *= 1e-9;
        mu = -1;
    } else {
        printf("Invalid choice.\n");
        return;
    }

    double R; 
    int n;
    
    printf("Enter lens R (mm): "); 
    if (scanf("%lf", &R) != 1) {
        clear_stdin();
        printf("Invalid input.\n");
        return;
    }
    
    printf("Enter ring order n: "); 
    if (scanf("%d", &n) != 1) {
        clear_stdin();
        printf("Invalid input.\n");
        return;
    }

    double R_m = R / 1000.0;
    double inside = ((2*n - 1) * lambda_med * R_m) / 2.0;
    double rn = sqrt(inside);
    double Dn = 2 * rn;

    printf("--------------------------------------------------\n");
    printf(" Bright Ring Results (Angstrom Included)\n");
    printf("--------------------------------------------------\n");
    printf("r_n = %.6e m | %.3f mm | %.3f A\n", rn, rn*1e3, to_angstrom(rn));
    printf("D_n = %.6e m | %.3f mm | %.3f A\n", Dn, Dn*1e3, to_angstrom(Dn));

    if (mu > 0) {
        double lambda_vac_calc = lambda_med * mu;
        printf("Lambda vacuum: %.3f A\n\n", to_angstrom(lambda_vac_calc));
    } else {
        printf("\n");
    }
}

// Function for Choice 3: Compute dark ring
void compute_dark_ring() {
    header("Dark Ring Calculator");

    int wchoice;
    printf("Enter 1 for lambda_vacuum (nm), 2 for lambda_medium (nm): ");
    if (scanf("%d", &wchoice) != 1) { 
        clear_stdin(); 
        printf("Invalid input.\n");
        return; 
    }

    double lambda_vac, lambda_med, mu;

    if (wchoice == 1) {
        printf("Enter lambda_vacuum (nm): ");
        if (scanf("%lf", &lambda_vac) != 1) {
            clear_stdin();
            printf("Invalid input.\n");
            return;
        }
        printf("Enter mu: ");
        if (scanf("%lf", &mu) != 1) {
            clear_stdin();
            printf("Invalid input.\n");
            return;
        }
        lambda_med = (lambda_vac * 1e-9) / mu;
    } else if (wchoice == 2) {
        printf("Enter lambda_medium (nm): ");
        if (scanf("%lf", &lambda_med) != 1) {
            clear_stdin();
            printf("Invalid input.\n");
            return;
        }
        lambda_med *= 1e-9;
        mu = -1;
    } else {
        printf("Invalid choice.\n");
        return;
    }

    double R; 
    int n;
    
    printf("Enter R (mm): ");
    if (scanf("%lf", &R) != 1) {
        clear_stdin();
        printf("Invalid input.\n");
        return;
    }
    
    printf("Enter order n: ");
    if (scanf("%d", &n) != 1) {
        clear_stdin();
        printf("Invalid input.\n");
        return;
    }

    double R_m = R / 1000.0;
    double rn = sqrt(n * lambda_med * R_m);
    double Dn = 2 * rn;

    printf("--------------------------------------------------\n");
    printf(" Dark Ring Results (Angstrom Included)\n");
    printf("--------------------------------------------------\n");
    printf("r_n = %.6e m | %.3f mm | %.3f A\n", rn, rn*1e3, to_angstrom(rn));
    printf("D_n = %.6e m | %.3f mm | %.3f A\n", Dn, Dn*1e3, to_angstrom(Dn));

    if (mu > 0) {
        double lambda_vac_calc = lambda_med * mu;
        printf("Lambda vacuum: %.3f A\n\n", to_angstrom(lambda_vac_calc));
    } else {
        printf("\n");
    }
}

// Main function with menu
int main(void) {
    header("Newton's Rings - Simulator / Calculator");
    printf("Formulas referenced from lab handout (Newton's Ring experiment).\n\n");

    while (1) {
        printf("==================================================\n");
        printf(" Choose an option:\n");
        printf("--------------------------------------------------\n");
        printf(" 1) Compute wavelength (λ) from Dn and Dn+p\n");
        printf(" 2) Compute radius/diameter of nth bright ring\n");
        printf(" 3) Compute radius/diameter of nth dark ring\n");
        printf(" 4) Exit\n");
        printf("==================================================\n");
        printf("Enter choice (1-4): ");

        int choice;
        if (scanf("%d", &choice) != 1) { 
            clear_stdin(); 
            printf("Invalid input.\n\n"); 
            continue; 
        }

        switch (choice) {
            case 1:
                compute_wavelength();
                break;
            case 2:
                compute_bright_ring();
                break;
            case 3:
                compute_dark_ring();
                break;
            case 4:
                header("Exiting Program");
                return 0;
            default:
                printf("Invalid choice! Try again.\n\n");
        }
    }

    return 0;
}
