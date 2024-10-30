#include <stdio.h>

#define size 3

int main() {
    double A[size * 2] = {1.0, 2.0, 3.5, -1.5, 4.0, 0.0};

    double B[size * 2] = {2.0, 3.0, -1.0, -4.0, 0.0, 1.5};

    double C[size * 2];

    for (int i = 0; i < size * 2; i++) {
        C[i] = A[i] + B[i];
    }

    double mrp = A[0];
    for (int i = 0; i < size; i++) {
        if (A[i*2] > mrp) {
            mrp = A[i * 2];
        }
    }

    int countneg = 0;
    for (int i = 0; i < size; i++) {
        if (B[i*2 + 1] < 0) {
            countneg++;
        }
    }

    double sumav = 0;
    for (int i = 0; i < size * 2; i++) {
        sumav += C[i];
    }
    double av = sumav / (size * 2);

    printf("Max RE A: %.2f\n", mrp);
    printf("Count IM less 0 B: %d\n", countneg);
    printf("Average value C: %.2f", av);
}
