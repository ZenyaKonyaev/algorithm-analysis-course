//
// Created by zenya2602 on 21.10.22.
//

#include "functions.h"
#include "matrix.h"
#include "matrix_math.h"
#include "time.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 255

void print_main_menu()
{
    printf("Select action you want to do:\n"
           "1) Multiply matrix\n"
           "2) Count time of realisations\n"
           "3) Exit\n"
           "Your action: ");

}

void print_menu_type_mul()
{
    printf("Select method of multiply matrix:\n"
           "1) Default algorithm\n"
           "2) Vinograd algorithm\n"
           "3) Optimized vinograd algorithm\n"
           "Type method: ");
}

int error_handler(int error_code)
{
    printf("Error! ");
    switch (error_code) {
        case ERROR_SELECT_ACTION_MAIN_MENU:
            printf("Action must be integer between 1 and 3!\n");
            break;
        case ERROR_SELECT_TYPE_ALG:
            printf("Type arg must be integer between 1 and 4!\n");
            break;
        /*case ERROR_SCAN_STR:
            printf("Something goes wrong in scan string!\n");
        case ERROR_LEN_STR:
            printf("Length of str must be less, than %d!\n", MAX_STR_LEN);*/
        default:
            printf("Unknown error!\n");
            break;
    }

    return error_code;
}

int enter_matrix(matrix_t **mat)
{
    int rows, cols;

    printf("Enter amount rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0)
        return ERROR_AMOUNT_ROWS;

    printf("Enter amount cols: ");
    if (scanf("%d", &cols) != 1 || cols <= 0)
        return ERROR_AMOUNT_COLS;

    *mat = create_matrix(rows, cols);

    printf("Enter elements of matrix:\n");
    for (int i = 0; i < rows; ++i) {
        printf("%d row: ", i + 1);
        for (int j = 0; j < cols; ++j)
            if (scanf("%d", &((*mat)->elements[i][j])) != 1) {
                free_matrix(*mat);
                return ERROR_ELEMENT_MATRIX;
            }
    }

    return EXIT_SUCCESS;
}

int action_multiply_matrix()
{
    matrix_t *mat_1, *mat_2;
    int rc = 0;

    printf("Enter first matrix:\n");
    if ((rc = enter_matrix(&mat_1)))
        return rc;

    printf("Enter second matrix:\n");
    if ((rc = enter_matrix(&mat_2))) {
        free_matrix(mat_1);
        return rc;
    }

    print_menu_type_mul();
    int type_alg;
    if (scanf("%d", &type_alg) != 1 || type_alg < 1 || type_alg > 3) {
        free_matrix(mat_1);
        free_matrix(mat_2);
        return ERROR_SELECT_TYPE_ALG;
    }

    matrix_t *res;
    switch (type_alg) {
        case DEFAULT_ALG:
            res = mul_matrix_def(mat_1, mat_2);
            break;
        case VINOGRAD_ALG:
            res = mul_matrix_vinograd(mat_1, mat_2);
            break;
        case VINOGRAD_OPTIMIZED_ALG:
            res = mul_matrix_vinograd_optimized(mat_1, mat_2);
            break;
        default:
            return -1;
    }

    printf("Result matrix:\n");
    print_matrix(res);

    free_matrix(res);

    return EXIT_SUCCESS;
}


void action_count_time()
{
#define AMOUNT_ITER 50
    matrix_t *(*arr_func[3])(matrix_t *, matrix_t *) = { mul_matrix_def, mul_matrix_vinograd, mul_matrix_vinograd_optimized};
    char *func_name[] = {"default", "vinograd", "vinograd optimized"};
    int dim_mat[] = {50, 100, 200, 300};

    for (int p = 0; p < 2; p++) {
        printf("%s dimension matrix:\n", p == 0 ? "Odd" : "Not odd");
        for (int i = 0; i < 4; ++i) {
            printf("Time for %d elements:\n", dim_mat[i] + p);
            for (int j = 0; j < 3; ++j) {
                matrix_t *m1 = create_matrix(dim_mat[i] + p, dim_mat[i] + p), *m2 = create_matrix(dim_mat[i] + p, dim_mat[i] + p);

                clock_t time = clock();
                for (int k = 0; k < AMOUNT_ITER; ++k) {
                    matrix_t *res = arr_func[j](m1, m2);
                    free_matrix(res);
                }
                time = clock() - time;

                free_matrix(m1);
                free_matrix(m2);

                printf("%s: %lf\n", func_name[j], time * 1.0 / AMOUNT_ITER);
            }
            printf("\n");
        }
    }
}
