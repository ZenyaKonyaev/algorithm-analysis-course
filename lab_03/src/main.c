#include "stdio.h"
#include "stdlib.h"
#include "functions.h"


//double getTimeSortedIncrease(size_t amountElements, int funcSort(int *, size_t))
//{
//    int totalTime = 0;
//    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
//    {
//        int *arr = malloc(amountElements * sizeof(int));
//        for (size_t i = 0; i < amountElements; ++i)
//            arr[i] = (int)i;
//
//        totalTime += funcSort(arr, amountElements);
//    }
//
//    return (float)totalTime / AMOUNT_SORTS;
//}
//
//double getTimeSortedDecrease(size_t amountElements, int funcSort(int *, size_t))
//{
//    int totalTime = 0;
//    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
//    {
//        int *arr = malloc(amountElements * sizeof(int));
//        for (size_t i = 0; i < amountElements; ++i)
//            arr[i] = (int)(amountElements - i);
//
//        totalTime += funcSort(arr, amountElements);
//    }
//
//    return (float)totalTime / AMOUNT_SORTS;
//}
//
//double getTimeSortedRandom(size_t amountElements, int funcSort(int *, size_t))
//{
//    int totalTime = 0; time_t t;
//    srand((unsigned) time(&t));
//
//    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
//    {
//        int *arr = malloc(amountElements * sizeof(int));
//        for (size_t i = 0; i < amountElements; ++i)
//            arr[i] = rand();
//
//        totalTime += funcSort(arr, amountElements);
//    }
//
//    return (float)totalTime / AMOUNT_SORTS;
//}
//
//void actionCharacteristicsSort()
//{
//    size_t amountElements = 10;
//
//    char *(sortsNames[3]) = {"Bubble sort", "Selection Sort", "Insertion Sort"};
//    int (*(sortsFunc[3])) (int *, size_t) = { &bubbleSort, &selectionSort, &insertionSort };
//    for(int i = 0; i < 4; ++i)
//    {
//        printf("\nAmount elements: %ld\n", amountElements);
//
//        for (int j = 0; j < 3; ++j)
//        {
//            printf("%s:\n", sortsNames[j]);
//            printf("Time sorted-increase array: %lf\n", getTimeSortedIncrease(amountElements, sortsFunc[j]));
//            printf("Time sorted-decrease array: %lf\n", getTimeSortedDecrease(amountElements, sortsFunc[j]));
//            printf("Time sorted-random array: %lf\n", getTimeSortedRandom(amountElements, sortsFunc[j]));
//        }
//
//        amountElements *= 10;
//    }
//}

int main()
{
    int action = 0;
    do {
        printStartMenu();

        scanf("%d", &action);

        switch (action) {
            case 1:
                actionSort();
                break;
            case 2:
                //actionCharacteristicsSort();
                break;
            case 3:
                break;
            default:
                printf("Error, there are no such action");
                break;
        }

    } while (action != 3);

    return EXIT_SUCCESS;
}



/*

50 проходов каждой сортровкой

Рандомные элементы от 0 до 100

Amount elements: 10
Bubble sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.000000
Time sorted-random array: 0.000000
Selection Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.000000
Time sorted-random array: 0.000000
Insertion Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.000000
Time sorted-random array: 0.000000

Amount elements: 100
Bubble sort:
Time sorted-increase array: 0.020000
Time sorted-decrease array: 0.020000
Time sorted-random array: 0.020000
Selection Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.000000
Time sorted-random array: 0.020000
Insertion Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.020000
Time sorted-random array: 0.000000

Amount elements: 1000
Bubble sort:
Time sorted-increase array: 1.020000
Time sorted-decrease array: 1.920000
Time sorted-random array: 2.040000
Selection Sort:
Time sorted-increase array: 1.120000
Time sorted-decrease array: 1.000000
Time sorted-random array: 0.900000
Insertion Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 1.400000
Time sorted-random array: 0.660000

Amount elements: 10000
Bubble sort:
Time sorted-increase array: 110.099998
Time sorted-decrease array: 183.839996
Time sorted-random array: 225.740005
Selection Sort:
Time sorted-increase array: 121.660004
Time sorted-decrease array: 100.300003
Time sorted-random array: 87.500000
Insertion Sort:
Time sorted-increase array: 0.060000
Time sorted-decrease array: 137.679993
Time sorted-random array: 68.239998


 Рандомные элементы неограничены

Amount elements: 10
Bubble sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.000000
Time sorted-random array: 0.000000
Selection Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.000000
Time sorted-random array: 0.000000
Insertion Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.000000
Time sorted-random array: 0.000000

Amount elements: 100
Bubble sort:
Time sorted-increase array: 0.020000
Time sorted-decrease array: 0.020000
Time sorted-random array: 0.020000
Selection Sort:
Time sorted-increase array: 0.020000
Time sorted-decrease array: 0.020000
Time sorted-random array: 0.020000
Insertion Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 0.020000
Time sorted-random array: 0.020000


 Amount elements: 1000
Bubble sort:
Time sorted-increase array: 1.020000
Time sorted-decrease array: 1.940000
Time sorted-random array: 2.020000
Selection Sort:
Time sorted-increase array: 1.260000
Time sorted-decrease array: 1.040000
Time sorted-random array: 0.960000
Insertion Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 1.480000
Time sorted-random array: 0.720000

Amount elements: 10000
Bubble sort:
Time sorted-increase array: 102.559998
Time sorted-decrease array: 187.800003
Time sorted-random array: 229.100006
Selection Sort:
Time sorted-increase array: 117.599998
Time sorted-decrease array: 103.320000
Time sorted-random array: 86.820000
Insertion Sort:
Time sorted-increase array: 0.000000
Time sorted-decrease array: 139.960007
Time sorted-random array: 69.400002


 */
