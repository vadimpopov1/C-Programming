#include "matrix_utils.h"

void create_addl_delta(
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

void create_addl_matrix(
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

double matrix_determiner(size_t size, double matrix[size][size]) {
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