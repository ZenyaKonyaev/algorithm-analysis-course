//
// Created by zenya2602 on 21.10.22.
//

#include "functions.h"
#include "matrix.h"
#include "levinstain.h"
#include "time.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 255

void print_main_menu()
{
    printf("Select action you want to do:\n"
           "1) Find distance between words\n"
           "2) Count time of realisations\n"
           "3) Exit\n"
           "Your action: ");

}

void print_menu_find_distance()
{
    printf("Select method of finding distance:\n"
           "1) Levenstain\n"
           "2) Damerau-Levenstain\n"
           "3) Damerau-Levenstain (rec.)\n"
           "4) Demerau-Levenstain (rec. & hash)\n"
           "Type method: ");
}

int error_handler(int error_code)
{
    printf("Error! ");
    switch (error_code) {
        case ERROR_SELECT_ACTION_MAIN_MENU:
            printf("Action must be integer between 1 and 3!\n");
            break;
        default:
            printf("Unknown error!\n");
            break;
    }

    return error_code;
}

int enter_str(char *str, char *message)
{
    printf("%s\n", message);
    str[MAX_STR_LEN] = '\0';
    if (scanf("%s", str) != 1)
        return ERROR_SCAN_STR;
    if (str[MAX_STR_LEN] != '\0')
        return ERROR_LEN_STR;

    return EXIT_SUCCESS;
}

int action_find_distance()
{
    int type_alg;
    print_menu_find_distance();

    if (scanf("%d", &type_alg) != 1 || type_alg < 1 || type_alg > 4)
        return ERROR_SELECT_TYPE_ALG;

    char word_1[MAX_STR_LEN + 1];
    char word_2[MAX_STR_LEN + 1];
    int rc;
    if ((rc = enter_str(word_1, "Enter first word:")) || (rc = enter_str(word_2, "Enter second word:")))
        return rc;

    int answer = 0;
    switch (type_alg) {
        case 1:
            answer = dist_lev(word_1, word_2, 1);
            break;
        case 2:
            answer = dist_dameray_lev(word_1, word_2, 1);
            break;
        case 3:
            answer = dist_dameray_lev_rec(word_1, word_2, strlen(word_1), strlen(word_2));
            break;
        case 4:
            answer = dist_dameray_lev_rec_hash(word_1, word_2);
            break;
        default:
            answer = -1;
            break;
    }

    printf("Founded distance: %d between %s and %s\n\n", answer, word_1, word_2);

    return EXIT_SUCCESS;
}

int get_min(int value_1, int value_2)
{
    if (value_1 < value_2)
        return value_1;
    return value_2;
}

void action_count_time()
{
#define AMOUNT_ITER 50
    char *arr[10] = { "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"};

    for (int i = 0; i < 10; ++i)
    {
        printf("Time for word consist %d chars:\n", i + 1);

        clock_t cur_time = clock();
        for (int j = 0; j < AMOUNT_ITER; ++j)
            dist_lev(arr[i], arr[i], 0);
        cur_time = clock() - cur_time;
        printf("Levenstain (iter.): %lf\n", cur_time * 1.0 / AMOUNT_ITER);

        cur_time = clock();
        for (int j = 0; j < AMOUNT_ITER; ++j)
            dist_dameray_lev(arr[i], arr[i], 0);
        cur_time = clock() - cur_time;
        printf("Dameray-Lev (iter.): %lf\n", cur_time * 1.0 / AMOUNT_ITER);

        cur_time = clock();
        for (int j = 0; j < AMOUNT_ITER; ++j)
            dist_dameray_lev_rec(arr[i], arr[i], strlen(arr[i]), strlen(arr[i]));
        cur_time = clock() - cur_time;
        printf("Dameray-Lev (rec.): %lf\n", cur_time * 1.0 / AMOUNT_ITER);

        cur_time = clock();
        for (int j = 0; j < AMOUNT_ITER; ++j)
            dist_dameray_lev_rec_hash(arr[i], arr[i]);
        cur_time = clock() - cur_time;
        printf("Dameray-Lev (rec. + hash.): %lf\n\n", cur_time * 1.0 / AMOUNT_ITER);
    }
}
