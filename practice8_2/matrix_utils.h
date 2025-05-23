#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <stddef.h>

void create_addl_matrix(size_t size, size_t i, double matrix[size][size], double addl_matrix[size - 1][size - 1]);
double matrix_determiner(size_t size, double matrix[size][size]);

#endif
