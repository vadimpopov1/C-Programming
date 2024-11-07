#include <stdio.h>

void ulitka(int n, int m[n][n]) {
    int cnt = 1; // значения
    int v = 0, b = n - 1; // v - верх b - низ
    int c = 0, r = n - 1; // c - лево r - право

    while (cnt <= n * n) {
        for (int i = c; i <= r; i++) { // верхняя строка
            m[v][i] = cnt++;
        }
        v++;

        for (int i = v; i <= b; i++) { // правая
            m[i][r] = cnt++;
        }
        r--;

        if (v <= b) {
            for (int i = r; i >= c; i--) { // нижняя
                m[b][i] = cnt++;
            }
            b--;
        }

        if (c <= r) {
            for (int i = b; i >= v; i--) { // правая
                m[i][c] = cnt++;
            }
            c++;
        }
    }
}

int main() {
    int n;

    printf("Введите размер матрицы: ");
    scanf("%d", &n);
    int m[n][n];
    ulitka(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }
}
