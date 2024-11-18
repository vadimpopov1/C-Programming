#include <stdio.h>
#include <math.h>

double solvepi(double pr) {
    double sum = 0.0;
    double term;
    int n = 1;

    do {
        term = pow(-1, n) / (2 * n - 1);
        sum += 4 * term;
        n++;
    } while (fabs(term) >= pr);

    return sum;
}

int main() {
    double pr;

    printf("Enter precision like 0.0001: ");
    scanf("%lf", &pr);
    if (pr > 0 && pr <= 0.1) {
        pr *= 0.1;
        double pia = solvepi(pr);
        int place = 0;
        double tpr = pr;
        while (tpr < 1) {
            tpr *= 10;
            place++;
        }
        printf("Your π ≈ %.*f\n", place-1, pia*(-1));
    } else {
        printf("Invalid precision. Check input");
    }
}
