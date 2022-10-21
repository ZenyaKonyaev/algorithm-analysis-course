//
// Created by zenya2602 on 21.10.22.
//

#include "matrix.h"
#include "levinstain.h"
#include "functions.h"

#include <string.h>
#include <stdio.h>

//qwertyuiop/wqreytiupo = 5
int dist_lev(char *str_1, char *str_2, int print_table_flag)
{
    matrix_t *d = create_matrix(strlen(str_1) + 1, strlen(str_2) + 1);

    d->elements[0][0] = 0;
    for (size_t i = 1; i < d->rows; ++i)
        d->elements[i][0] = i;
    for (size_t i = 1; i < d->cols; ++i)
        d->elements[0][i] = i;

    for (size_t i = 1; i < d->rows; ++i)
        for (size_t j = 1; j < d->cols; ++j) {
            int offset = str_1[i - 1] == str_2[j - 1] ? 0 : 1;
            d->elements[i][j] = get_min(d->elements[i][j - 1] + 1,
                                        get_min(d->elements[i - 1][j] + 1,
                                                d->elements[i - 1][j - 1] + offset));
        }

    if (print_table_flag) {
        printf("Levinstain distance table:\n");
        print_matrix(d);
    }

    int res = d->elements[d->rows - 1][d->cols - 1];
    free_matrix(d);

    return res;
}

int dist_dameray_lev(char *str_1, char *str_2, int print_table_flag)
{
    matrix_t *d = create_matrix(strlen(str_1) + 1, strlen(str_2) + 1);

    d->elements[0][0] = 0;
    for (size_t i = 1; i < d->rows; ++i)
        d->elements[i][0] = i;
    for (size_t i = 1; i < d->cols; ++i)
        d->elements[0][i] = i;

    for (size_t i = 1; i < d->rows; ++i)
        for (size_t j = 1; j < d->cols; ++j) {
            int offset = str_1[i - 1] == str_2[j - 1] ? 0 : 1;
            d->elements[i][j] = get_min(d->elements[i][j - 1] + 1,
                                        get_min(d->elements[i - 1][j] + 1,
                                                d->elements[i - 1][j - 1] + offset));
            if (j > 1 && i > 1 && str_1[i - 1] == str_2[j - 2] && str_1[i - 2] == str_2[j - 1])
                d->elements[i][j] = get_min(d->elements[i][j], d->elements[i - 2][j - 2] + 1);
        }

    if (print_table_flag) {
        printf("Damerau-Levenstain distance table:\n");
        print_matrix(d);
    }

    int res = d->elements[d->rows - 1][d->cols - 1];
    free_matrix(d);

    return res;
}

//qwertyuiop/wqreytiupo = 5
int dist_dameray_lev_rec(char *str_1, char *str_2, int len_1, int len_2)
{
    if (len_1 == 0)
        return len_2;
    if (len_2 == 0)
        return len_1;

    int offset = str_1[len_1 - 1] == str_2[len_2 - 1] ? 0 : 1;
    int res = get_min(dist_dameray_lev_rec(str_1, str_2, len_1 - 1, len_2) + 1,
                     get_min(dist_dameray_lev_rec(str_1, str_2, len_1, len_2 - 1) + 1,
                             dist_dameray_lev_rec(str_1, str_2, len_1 - 1, len_2 - 1) + offset));
    if (len_1 > 1 && len_2 > 1 && str_1[len_1 - 1] == str_2[len_2 - 2] && str_1[len_1 - 2] == str_2[len_2 - 1])
        res = get_min(res, dist_dameray_lev_rec(str_1, str_2, len_1 - 2, len_2 - 2) + 1);

    return res;
}

int dist_dameray_lev_rec_hash_call(char *str_1, char *str_2, int len_1, int len_2, matrix_t *mat)
{
    if (len_1 == 0)
        return (mat->elements)[len_1][len_2] = len_2;
    if (len_2 == 0)
        return (mat->elements)[len_1][len_2] = len_1;

    if (mat->elements[len_1 - 1][len_2] == -1)
        dist_dameray_lev_rec_hash_call(str_1, str_2, len_1 - 1, len_2, mat);
    if (mat->elements[len_1][len_2 - 1] == -1)
        dist_dameray_lev_rec_hash_call(str_1, str_2, len_1, len_2 - 1, mat);
    if (mat->elements[len_1 - 1][len_2 - 1] == -1)
        dist_dameray_lev_rec_hash_call(str_1, str_2, len_1 - 1, len_2 - 1, mat);

    int offset = str_1[len_1 - 1] == str_2[len_2 - 1] ? 0 : 1;
    mat->elements[len_1][len_2] = get_min(mat->elements[len_1][len_2 - 1] + 1,
                                get_min(mat->elements[len_1 - 1][len_2] + 1,
                                        mat->elements[len_1 - 1][len_2 - 1] + offset));
    if (len_1 > 1 && len_2 > 1 && str_1[len_1 - 1] == str_2[len_2 - 2] && str_1[len_1 - 2] == str_2[len_2 - 1]) {
        if (mat->elements[len_1 - 2][len_2 - 2] == -1)
            dist_dameray_lev_rec_hash_call(str_1, str_2, len_1 - 2, len_2 - 2, mat);
        mat->elements[len_1][len_2] = get_min(mat->elements[len_1][len_2], mat->elements[len_1 - 2][len_2 - 2] + 1);
    }

    return mat->elements[len_1][len_2];
}

int dist_dameray_lev_rec_hash(char *str_1, char *str_2)
{
    matrix_t *d = create_matrix(strlen(str_1) + 1, strlen(str_2) + 1);
    clear_matrix_elems(d);

    int res = dist_dameray_lev_rec_hash_call(str_1, str_2, strlen(str_1), strlen(str_2), d);
    free_matrix(d);

    return res;
}
