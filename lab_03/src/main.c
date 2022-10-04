#include "stdio.h"
#include "stdlib.h"
#include "functions.h"
#include "timeCounter.h"

int main()
{
    int action = 0;
    do {
        printStartMenu();

        if (scanf("%d", &action) != 1) {
            printerError(ERROR_INPUT_ACTION);
            return ERROR_INPUT_ACTION;
        }

        int error = 0;
        switch (action) {
            case 1:
                error = actionSort();
                break;
            case 2:
                actionCharacteristicsSort();
                break;
            case 3:
                break;
            default:
                printf("Error, there are no such action");
                break;
        }

        if (error) {
            printerError(error);
            return error;
        }

    } while (action != 3);

    return EXIT_SUCCESS;
}



/*

100 проходов каждой сортровкой

Amount elements: 10
combSort:
Time sorted-increase array: 1.500000
Time sorted-decrease array: 1.540000
Time sorted-random array (numbers from 0 to 1000): 1.800000
Time sorted-random array (numbers from 0 to 3): 1.660000
Time sorted-random array (numbers from 0 to 10000): 1.790000

bucketSort:
Time sorted-increase array: 2.040000
Time sorted-decrease array: 2.090000
Time sorted-random array (numbers from 0 to 1000): 2.470000
Time sorted-random array (numbers from 0 to 3): 2.190000
Time sorted-random array (numbers from 0 to 10000): 1.740000

bitonicSort:
Time sorted-increase array: 2.460000
Time sorted-decrease array: 2.610000
Time sorted-random array (numbers from 0 to 1000): 2.360000
Time sorted-random array (numbers from 0 to 3): 2.300000
Time sorted-random array (numbers from 0 to 10000): 2.370000


--------

 Amount elements: 100
combSort:
Time sorted-increase array: 7.880000
Time sorted-decrease array: 9.600000
Time sorted-random array (numbers from 0 to 1000): 12.380000
Time sorted-random array (numbers from 0 to 3): 8.890000
Time sorted-random array (numbers from 0 to 10000): 12.490000

bucketSort:
Time sorted-increase array: 7.610000
Time sorted-decrease array: 7.710000
Time sorted-random array (numbers from 0 to 1000): 12.780000
Time sorted-random array (numbers from 0 to 3): 8.080000
Time sorted-random array (numbers from 0 to 10000): 11.290000

bitonicSort:
Time sorted-increase array: 27.370001
Time sorted-decrease array: 28.490000
Time sorted-random array (numbers from 0 to 1000): 39.790001
Time sorted-random array (numbers from 0 to 3): 31.940001
Time sorted-random array (numbers from 0 to 10000): 34.299999


--------




Amount elements: 1000
combSort:
Time sorted-increase array: 113.080002
Time sorted-decrease array: 130.279999
Time sorted-random array (numbers from 0 to 1000): 189.440002
Time sorted-random array (numbers from 0 to 3): 126.389999
Time sorted-random array (numbers from 0 to 10000): 197.399994

bucketSort:
Time sorted-increase array: 100.449997
Time sorted-decrease array: 96.400002
Time sorted-random array (numbers from 0 to 1000): 189.770004
Time sorted-random array (numbers from 0 to 3): 100.660004
Time sorted-random array (numbers from 0 to 10000): 163.460007

bitonicSort:
Time sorted-increase array: 428.130005
Time sorted-decrease array: 390.859985
Time sorted-random array (numbers from 0 to 1000): 486.029999
Time sorted-random array (numbers from 0 to 3): 405.619995
Time sorted-random array (numbers from 0 to 10000): 576.289978


--------


Amount elements: 10000
combSort:
Time sorted-increase array: 1750.810059
Time sorted-decrease array: 2066.090088
Time sorted-random array (numbers from 0 to 1000): 2491.199951
Time sorted-random array (numbers from 0 to 3): 1763.359985
Time sorted-random array (numbers from 0 to 10000): 2739.149902

bucketSort:
Time sorted-increase array: 801.570007
Time sorted-decrease array: 888.500000
Time sorted-random array (numbers from 0 to 1000): 1975.790039
Time sorted-random array (numbers from 0 to 3): 1286.040039
Time sorted-random array (numbers from 0 to 10000): 2997.110107

bitonicSort:
Time sorted-increase array: 12427.690430
Time sorted-decrease array: 11475.059570
Time sorted-random array (numbers from 0 to 1000): 12273.070312
Time sorted-random array (numbers from 0 to 3): 11061.610352
Time sorted-random array (numbers from 0 to 10000): 11820.120117


--------


 */
