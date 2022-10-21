#include <stdlib.h>
#include <stdio.h>

#include "functions.h"


int main()
{
    int action, rc;

    do {

        print_main_menu();
        if (scanf("%d", &action) != 1 || action < ACTION_FIND_DISTANCE || action  > ACTION_EXIT_MENU)
            return error_handler(ERROR_SELECT_ACTION_MAIN_MENU);

        switch (action) {
            case ACTION_FIND_DISTANCE:
                if ((rc = action_find_distance()))
                    return error_handler(rc);
                break;
            case ACTION_COUNT_TIME:
                action_count_time();
                break;
            case ACTION_EXIT_MENU:
                break;
            default:
                return error_handler(1);
        }

    } while (action != ACTION_EXIT_MENU);

    return EXIT_SUCCESS;
}
