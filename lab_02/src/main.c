#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main()
{
    int action;

    do {
        print_main_menu();

        if (scanf("%d", &action) != 1 || action < ACTION_MULTIPLY_MATRIX || action > ACTION_EXIT_MENU)
            return error_handler(ERROR_SELECT_ACTION_MAIN_MENU);

        int rc;
        switch (action) {
            case ACTION_MULTIPLY_MATRIX:
                if ((rc = action_multiply_matrix()))
                    error_handler(rc);
                break;
            case ACTION_COUNT_TIME:
                action_count_time();
                break;
            case ACTION_EXIT_MENU:
                break;
            default:
                return error_handler(-1);
        }
    } while (action != ACTION_EXIT_MENU);

    return EXIT_SUCCESS;
}

/*
Odd dimension matrix:
Time for 50 elements:
default: 1137.100000
vinograd: 623.760000
vinograd optimized: 536.480000

Time for 100 elements:
default: 5678.200000
vinograd: 4446.780000
vinograd optimized: 4155.260000

Time for 200 elements:
default: 45255.220000
vinograd: 41572.300000
vinograd optimized: 34487.400000

Time for 300 elements:
default: 155263.700000
vinograd: 129265.100000
vinograd optimized: 126086.420000

Not odd dimension matrix:
Time for 51 elements:
default: 695.600000
vinograd: 614.100000
vinograd optimized: 574.820000

Time for 101 elements:
default: 5928.780000
vinograd: 4484.280000
vinograd optimized: 4324.300000

Time for 201 elements:
default: 44531.320000
vinograd: 36619.080000
vinograd optimized: 34975.720000

Time for 301 elements:
default: 158599.400000
vinograd: 130065.340000
vinograd optimized: 133109.720000
 */
