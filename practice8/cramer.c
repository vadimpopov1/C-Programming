#include <stdio.h>
#include <stdlib.h>

double deter(double m[10][10], int n) {
    double det = 0;
    if (n == 1) {
        return m[0][0];
    }
    if (n == 2) {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    double temp[10][10];
    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x)
                    continue;
                temp[subi][subj] = m[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * m[0][x] * deter(temp, n - 1);
    }
    return det;
}

void cramer(double m[10][10], double results[10], int n) {
    double det = deter(m, n);
    if (det == 0) {
        printf("Система не имеет единственного решения. \n");
        return;
    }

    double x[10];
    for (int i = 0; i < n; i++) {
        double temp[10][10];
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (k == i) {
                    temp[j][k] = results[j]; 
                } else {
                    temp[j][k] = m[j][k]; 
                }
            }
        }
        x[i] = deter(temp, n) / det;
    }


    printf("Решение системы: \n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.1lf\n", i + 1, x[i]);
    }
}

int main() {
    int n;
    double m[10][10], res[10];

    printf("Введите количество уравнений: ");
    scanf("%d", &n);

    printf("Введите коэффициенты матрицы: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &m[i][j]);
        }
    }

    printf("Введите свободные члены: \n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &res[i]);
    }

    cramer(m, res, n);

    return 0;
}
