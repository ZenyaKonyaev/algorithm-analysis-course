//
// Created by zenya2602 on 21.10.22.
//

#ifndef SRC_FUNCTIONS_H
#define SRC_FUNCTIONS_H

#define ERROR_SELECT_ACTION_MAIN_MENU 1
#define ERROR_SELECT_TYPE_ALG 2
#define ERROR_SCAN_STR 3
#define ERROR_LEN_STR 4

#define ACTION_FIND_DISTANCE 1
#define ACTION_COUNT_TIME 2
#define ACTION_EXIT_MENU 3

void print_main_menu();
int error_handler(int error_code);
int get_min(int value_1, int value_2);
int action_find_distance();
void action_count_time();


#endif //SRC_FUNCTIONS_H
