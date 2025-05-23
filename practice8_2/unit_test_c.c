#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "matrix_utils.h"  // функции

// Тест для 1x1
static void test_determinant_1x1(void **state) {
    (void) state;

    double matrix[1][1] = {
        {42}
    };
    double result = matrix_determiner(1, matrix);
    assert_float_equal(result, 42.0, 0.001);
}

// Тест для 2х2
static void test_determinant_2x2(void **state) {
    (void) state;

    double matrix[2][2] = {
        {4, 6},
        {3, 8}
    };
    double result = matrix_determiner(2, matrix);
    assert_float_equal(result, 14.0, 0.001);
}

// Тест для 3x3 матрицы
static void test_determinant_3x3(void **state) {
    (void) state;

    double matrix[3][3] = {
        {6, 1, 1},
        {4, -2, 5},
        {2, 8, 7}
    };
    double result = matrix_determiner(3, matrix);
    assert_float_equal(result, -306.0, 0.001); // 306
}

// Тест для 4x4 матрицы
static void test_determinant_4x4(void **state) {
    (void) state;

    double matrix[4][4] = {
        {1, 2, 3, 4},
        {0, 5, 6, 7},
        {0, 0, 8, 9},
        {0, 0, 0, 10}
    };
    double result = matrix_determiner(4, matrix);
    assert_float_equal(result, 1 * 5 * 8 * 10, 0.001);
}

// Тест для матрицы 3x3 (единичная матрица)
static void test_determinant_identity_matrix(void **state) {
    (void) state;

    double matrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    double result = matrix_determiner(3, matrix);
    assert_float_equal(result, 1.0, 0.001); // 1
}

// Тест для произвольной матрицы с заранее вычисленным определителем
static void test_determinant_arbitrary(void **state) {
    (void) state;

    double matrix[3][3] = {
        {3, 2, 1},
        {1, 3, 1},
        {2, 2, 4}
    };
    double result = matrix_determiner(3, matrix);
    assert_float_equal(result, 22.0, 0.001); // 22
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_determinant_1x1),
        cmocka_unit_test(test_determinant_2x2),
        cmocka_unit_test(test_determinant_3x3),
        cmocka_unit_test(test_determinant_4x4),
        cmocka_unit_test(test_determinant_identity_matrix),
        cmocka_unit_test(test_determinant_arbitrary),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
