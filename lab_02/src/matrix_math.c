//
// Created by zenya2602 on 22.10.22.
//

#include "matrix_math.h"

matrix_t *mul_matrix_def(matrix_t *first_mat, matrix_t *second_mat)
{
    matrix_t *res = create_matrix(first_mat->rows, second_mat->cols);

    int eq_dim = first_mat->cols;

    for (int i = 0; i < res->rows; ++i) {
        for (int j = 0; j < res->cols; ++j) {
            (res->elements)[i][j] = 0;
            for (int k = 0; k < eq_dim; ++k) {
                (res->elements)[i][j] += (first_mat->elements)[i][k] * (second_mat->elements)[k][j];
            }
        }
    }

    return res;
}

matrix_t *mul_matrix_vinograd(matrix_t *first_mat, matrix_t *second_mat)
{
    matrix_t *res = create_matrix(first_mat->rows, second_mat->cols);
    int *factorA = calloc(first_mat->rows, sizeof(int));
    int *factorB = calloc(second_mat->cols, sizeof(int));

    int eq_dim = first_mat->cols;

    for (int i = 0; i < first_mat->rows; ++i)
        for (int j = 0; j < eq_dim / 2; ++j)
            factorA[i] = factorA[i] + (first_mat->elements)[i][2 * j] * (first_mat->elements)[i][2 * j + 1];

    for (int i = 0; i < second_mat->cols; ++i)
        for (int j = 0; j < eq_dim / 2; ++j)
            factorB[i] = factorB[i] + (second_mat->elements)[2 * j][i] * (second_mat->elements)[2 * j + 1][i];

    for (int i = 0; i < res->rows; ++i) {
        for (int j = 0; j < res->cols; ++j) {
            (res->elements)[i][j] = -factorA[i] - factorB[j];
            for (int k = 0; k < eq_dim / 2; ++k) {
                (res->elements)[i][j] = (res->elements)[i][j] + ((first_mat->elements)[i][2 * k] + (second_mat->elements)[2 * k + 1][j]) * ((first_mat->elements)[i][2 * k + 1] + (second_mat->elements)[2 * k][j]);
            }
        }
    }

    if (eq_dim % 2 != 0) {
        for (int i = 0; i < res->rows; ++i)
            for (int j = 0; j < res->cols; ++j)
                (res->elements)[i][j] = (res->elements)[i][j] + (first_mat->elements)[i][first_mat->cols - 1] * (second_mat->elements)[second_mat->rows - 1][j];
    }

    free(factorA);
    free(factorB);

    return res;
}

matrix_t *mul_matrix_vinograd_optimized(matrix_t *first_mat, matrix_t *second_mat)
{
    matrix_t *res = create_matrix(first_mat->rows, second_mat->cols);
    int *factorA = calloc(first_mat->rows, sizeof(int));
    int *factorB = calloc(second_mat->cols, sizeof(int));

    int eq_dim = first_mat->cols;
    int half_eq_dim = eq_dim >> 1;

    for (int i = 0; i < first_mat->rows; ++i)
        for (int j = 0; j < half_eq_dim; ++j)
            factorA[i] += (first_mat->elements)[i][j << 1] * (first_mat->elements)[i][(j << 1) + 1];

    for (int i = 0; i < second_mat->cols; ++i)
        for (int j = 0; j < half_eq_dim; ++j)
            factorB[i] += (second_mat->elements)[j << 1][i] * (second_mat->elements)[(j << 1) + 1][i];

    for (int i = 0; i < res->rows; ++i) {
        for (int j = 0; j < res->cols; ++j) {
            (res->elements)[i][j] = -factorA[i] - factorB[j];
            for (int k = 0; k < half_eq_dim; ++k) {
                (res->elements)[i][j] += ((first_mat->elements)[i][k << 1] + (second_mat->elements)[(k << 1) + 1][j]) * ((first_mat->elements)[i][(k << 1) + 1] + (second_mat->elements)[(k << 1)][j]);
            }
        }
    }

    if (eq_dim % 2 != 0) {
        for (int i = 0; i < res->rows; ++i)
            for (int j = 0; j < res->cols; ++j)
                (res->elements)[i][j] += (first_mat->elements)[i][first_mat->cols - 1] * (second_mat->elements)[second_mat->rows - 1][j];
    }

    free(factorA);
    free(factorB);

    return res;
}
