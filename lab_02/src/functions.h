//
// Created by zenya2602 on 21.10.22.
//

#ifndef SRC_FUNCTIONS_H
#define SRC_FUNCTIONS_H

#define ERROR_SELECT_ACTION_MAIN_MENU 1
#define ERROR_SELECT_TYPE_ALG 2
#define ERROR_AMOUNT_ROWS 3
#define ERROR_AMOUNT_COLS 4
#define ERROR_ELEMENT_MATRIX 5

#define DEFAULT_ALG 1
#define VINOGRAD_ALG 2
#define VINOGRAD_OPTIMIZED_ALG 3

#define ACTION_MULTIPLY_MATRIX 1
#define ACTION_COUNT_TIME 2
#define ACTION_EXIT_MENU 3

void print_main_menu();
int error_handler(int error_code);
int action_multiply_matrix();
void action_count_time();


#endif //SRC_FUNCTIONS_H
