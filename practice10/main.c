#include <stdio.h>
#include <stdlib.h>
#include "romb.h"

int main() {
    size_t n;
    
    printf("Введите количество ромбов: ");
    if (scanf("%zu", &n) != 1 || n == 0) {
        printf("Ошибка ввода. Введите положительное число.\n");
        return 1;
    }

    Romb *rhombs = malloc(n * sizeof(Romb));
    if (rhombs == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    int count_sq = 0;
    float min_area_val = -1.0f;
    Romb min_area;

    for (size_t i = 0; i < n; i++) {
        printf("Введите первую диагональ для ромба %zu: ", i + 1);
        while (scanf("%f", &rhombs[i].d1) != 1) {
            printf("Ошибка ввода. Попробуйте снова: ");
            while (getchar() != '\n'); 
        }

        printf("Введите вторую диагональ для ромба %zu: ", i + 1);
        while (scanf("%f", &rhombs[i].d2) != 1) {
            printf("Ошибка ввода. Попробуйте снова: ");
            while (getchar() != '\n'); 
        }

        if (is_square(rhombs[i])) {
            count_sq++;
        }

        float cur_area = area(rhombs[i]);
        if (min_area_val < 0.0f || cur_area < min_area_val) {
            min_area_val = cur_area;
            min_area = rhombs[i];
        }
    }

    printf("Количество квадратов: %d\n", count_sq);
    printf("Ромб с минимальной площадью: d1=%.2f, d2=%.2f, площадь=%.2f\n",
           min_area.d1, min_area.d2, min_area_val);

    free(rhombs);
    return 0;
}
