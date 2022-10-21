//
// Created by zenya2602 on 21.10.22.
//

#ifndef SRC_MATRIX_H
#define SRC_MATRIX_H

#include "stdlib.h"

typedef struct {
    int **elements;
    size_t rows;
    size_t cols;
} matrix_t;

matrix_t *create_matrix(int row, int col);
void clear_matrix_elems(matrix_t *mat);
void free_matrix(matrix_t *mat);
void print_matrix(matrix_t *mat);

#endif //SRC_MATRIX_H
