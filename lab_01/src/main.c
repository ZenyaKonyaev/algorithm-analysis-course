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

/*
Time for word consist 1 chars:
Levenstain (iter.): 0.200000
Dameray-Lev (iter.): 0.160000
Dameray-Lev (rec.): 0.140000
Dameray-Lev (rec. + hash.): 0.320000

Time for word consist 2 chars:
Levenstain (iter.): 0.300000
Dameray-Lev (iter.): 0.320000
Dameray-Lev (rec.): 0.240000
Dameray-Lev (rec. + hash.): 0.620000

Time for word consist 3 chars:
Levenstain (iter.): 0.560000
Dameray-Lev (iter.): 0.680000
Dameray-Lev (rec.): 1.120000
Dameray-Lev (rec. + hash.): 1.000000

Time for word consist 4 chars:
Levenstain (iter.): 0.760000
Dameray-Lev (iter.): 1.000000
Dameray-Lev (rec.): 4.260000
Dameray-Lev (rec. + hash.): 1.300000

Time for word consist 5 chars:
Levenstain (iter.): 1.020000
Dameray-Lev (iter.): 1.300000
Dameray-Lev (rec.): 21.700000
Dameray-Lev (rec. + hash.): 1.720000

Time for word consist 6 chars:
Levenstain (iter.): 0.800000
Dameray-Lev (iter.): 1.600000
Dameray-Lev (rec.): 127.280000
Dameray-Lev (rec. + hash.): 2.180000

Time for word consist 7 chars:
Levenstain (iter.): 1.100000
Dameray-Lev (iter.): 2.000000
Dameray-Lev (rec.): 567.960000
Dameray-Lev (rec. + hash.): 2.300000

Time for word consist 8 chars:
Levenstain (iter.): 1.240000
Dameray-Lev (iter.): 2.300000
Dameray-Lev (rec.): 3170.120000
Dameray-Lev (rec. + hash.): 3.080000

Time for word consist 9 chars:
Levenstain (iter.): 1.420000
Dameray-Lev (iter.): 2.300000
Dameray-Lev (rec.): 18337.360000
Dameray-Lev (rec. + hash.): 3.640000

Time for word consist 10 chars:
Levenstain (iter.): 1.940000
Dameray-Lev (iter.): 2.380000
Dameray-Lev (rec.): 102172.820000
Dameray-Lev (rec. + hash.): 4.200000
 */
