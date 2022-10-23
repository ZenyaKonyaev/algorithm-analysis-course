//
// Created by zenya2602 on 22.10.22.
//

#ifndef SRC_MATRIX_MATH_H
#define SRC_MATRIX_MATH_H

#include "matrix.h"

matrix_t *mul_matrix_def(matrix_t *first_mat, matrix_t *second_mat);
matrix_t *mul_matrix_vinograd(matrix_t *first_mat, matrix_t *second_mat);
matrix_t *mul_matrix_vinograd_optimized(matrix_t *first_mat, matrix_t *second_mat);


#endif //SRC_MATRIX_MATH_H
