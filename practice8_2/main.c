// Author - https://github.com/Emeteil/C-learning/blob/main/Практическое_задание_8/task_for_5.c

#include <stdio.h>

void create_addl_delta( // 1
        size_t size,
        size_t i,
        double matrix[size][size],
        double right_side[size],
        double addl_matrix[size][size]
    ) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (i == y) {
                addl_matrix[x][y] = right_side[x];
                continue;
            }
            addl_matrix[x][y] = matrix[x][y];
        }
    }
}

void create_addl_matrix( // 2
        size_t size,
        size_t i,
        double matrix[size][size],
        double addl_matrix[size - 1][size - 1]
    ) {
    int new_y = 0;
    for (int x = 1; x < size; x++) {
        new_y = 0;
        for (int y = 0; y < size; y++) {
            if (y == i) continue;
            addl_matrix[x - 1][new_y] = matrix[x][y];
            new_y++;
        }
    }
}

double matrix_determiner(size_t size, double matrix[size][size]) { // 3
    if (size == 1) return matrix[0][0];

    double sum = 0;
    for (int i = 0; i < size; i++) {
        size_t addl_size = size - 1;
        double addl_matrix[addl_size][addl_size];
        create_addl_matrix(size, i, matrix, addl_matrix);
        double multiplier = matrix_determiner(addl_size, addl_matrix);
        sum += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * multiplier;
    }
    
    return sum;
}

int main() {
    size_t N = 0;

    printf("N: ");
    scanf("%zu", &N);

    if (N < 2) {
        puts("Данные введены некоректно!");
        return 1;
    }
    
    double matrix[N][N];
    double right_side[N];

    for (int i = 0; i < N; i++) {
        printf("Уравнение №%d:\n", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%c * ", 97 + j);
            scanf("%lf", matrix[i] + j);
        }
        printf("= ");
        scanf("%lf", right_side + i);
    }

    puts("-------");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%0.1lf%c ", matrix[i][j], 97 + j);
            if (j != N - 1) printf("+ ");
        }
        printf("= %0.1lf\n", right_side[i]);
    }
    puts("-------");

    printf("Ответ: ");
    double delta = matrix_determiner(N, matrix);
    if (!delta) {
        puts("Нет единственного решения.");
        return 1;
    }

    puts("");
    double new_delta_matrix[N][N];
    double new_delta;
    for (int i = 0; i < N; i++) {
        create_addl_delta(N, i, matrix, right_side, new_delta_matrix);
        new_delta = matrix_determiner(N, new_delta_matrix);
        printf("%c = %0.2lf\n", 97 + i, new_delta/delta);
    }

    return 0;
}