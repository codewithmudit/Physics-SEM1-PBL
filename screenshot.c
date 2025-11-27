#include <stdio.h>
#include <math.h>

double to_angstrom(double lambda_m) {
    return lambda_m * 1e10;
}

void compute_wavelength() {
    printf("\n** Compute Wavelength from Diameters **\n\n");
    
    double Dn, Dnp, R, mu;
    int n, p;

    printf("Enter diameter Dn (mm): ");
    scanf("%lf", &Dn);
    printf("Enter diameter Dn+p (mm): ");
    scanf("%lf", &Dnp);
    printf("Enter order n: ");
    scanf("%d", &n);
    printf("Enter p (>0): ");
    scanf("%d", &p);
    printf("Enter radius of curvature R (mm): ");
    scanf("%lf", &R);
    printf("Enter refractive index mu: ");
    scanf("%lf", &mu);

    double Dn_m = Dn / 1000.0;
    double Dnp_m = Dnp / 1000.0;
    double R_m = R / 1000.0;

    double numerator = (Dnp_m * Dnp_m) - (Dn_m * Dn_m);
    double lambda_med = numerator / (4.0 * p * R_m);
    double lambda_vac = mu * lambda_med;

    printf("\n--------------------------------------------------\n");
    printf("Lambda (medium): %.6e m  | %.3f A\n", lambda_med, to_angstrom(lambda_med));
    printf("Lambda (vacuum): %.6e m  | %.3f A\n\n", lambda_vac, to_angstrom(lambda_vac));
}

void compute_bright_ring() {
    printf("\n** Bright Ring Calculator **\n\n");

    int wchoice;
    printf("Enter 1 for lambda_vacuum (nm), 2 for lambda_medium (nm): ");
    scanf("%d", &wchoice);

    double lambda_vac, lambda_med, mu;

    if (wchoice == 1) {
        printf("Enter lambda_vacuum (nm): ");
        scanf("%lf", &lambda_vac);
        printf("Enter refractive index mu: ");
        scanf("%lf", &mu);
        lambda_med = (lambda_vac * 1e-9) / mu;
    } else {
        printf("Enter lambda_medium (nm): ");
        scanf("%lf", &lambda_med);
        lambda_med *= 1e-9;
        mu = -1;
    }

    double R; 
    int n;
    
    printf("Enter lens R (mm): "); 
    scanf("%lf", &R);
    printf("Enter ring order n: "); 
    scanf("%d", &n);

    double R_m = R / 1000.0;
    double inside = ((2*n - 1) * lambda_med * R_m) / 2.0;
    double rn = sqrt(inside);
    double Dn = 2 * rn;

    printf("\n--------------------------------------------------\n");
    printf("r_n = %.6e m | %.3f mm | %.3f A\n", rn, rn*1e3, to_angstrom(rn));
    printf("D_n = %.6e m | %.3f mm | %.3f A\n", Dn, Dn*1e3, to_angstrom(Dn));

    if (mu > 0) {
        double lambda_vac_calc = lambda_med * mu;
        printf("Lambda vacuum: %.3f A\n\n", to_angstrom(lambda_vac_calc));
    }
}

void compute_dark_ring() {
    printf("\n** Dark Ring Calculator **\n\n");

    int wchoice;
    printf("Enter 1 for lambda_vacuum (nm), 2 for lambda_medium (nm): ");
