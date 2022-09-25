#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define AMOUNT_SORTS 50

int bubbleSort(int *arr, size_t n)
{
    clock_t timeStart, timeEnd;

    timeStart = clock();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    timeEnd = clock();

    return timeEnd - timeStart;
}


//4 2 9 2 5
int selectionSort(int *arr, size_t n)
{
    clock_t timeStart, timeEnd;

    timeStart = clock();
    for (int i = 0; i < n; ++i) {
        int idxToSwap = 0;
        for (int j = 0; j < n - i; ++j) {
            if (arr[idxToSwap] < arr[j]) { //максимум
                idxToSwap = j;
            }
        }
        int tmp = arr[idxToSwap];
        arr[idxToSwap] = arr[n - i - 1];
        arr[n - i - 1] = tmp;
    }
    timeEnd = clock();

    return timeEnd - timeStart;
}

int insertionSort(int *arr, size_t n)
{
    clock_t timeStart, timeEnd;

    timeStart = clock();
    for (int i = 0; i < n; ++i) {
        int idxInsert = i;
        int insertElement = arr[i];
        for (int j = i; j > 0 && arr[j - 1] > insertElement; --j) {
            arr[j] = arr[j - 1];
            idxInsert = j - 1;
        }
        arr[idxInsert] = insertElement;
    }
    timeEnd = clock();

    return timeEnd - timeStart;
}

void printStartMenu()
{
    printf("Chose action:\n"
           "1) Sort array\n"
           "2) Get characteristics sort algorithms\n"
           "3) Exit\n");
}

void printSortMenu()
{
    printf("Chose type of sort:\n"
           "1) Bubble sort\n"
           "2) Insertion sort\n"
           "3) Selection sort\n");
}

void getArrElements(int **arr, size_t *len)
{
    printf("Enter amount elements:\n");
    scanf("%ld", len);

    *arr = malloc(*len * sizeof(int));

    printf("Enter elements:\n");
    for (size_t i = 0; i < *len; ++i)
        scanf("%d", (*arr) + i);

}

void printArray(int *arr, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void actionSelectTypeSort(int funcSort(int *, size_t))
{
    int *arr; size_t len;
    getArrElements(&arr, &len);

    funcSort(arr, len);

    printf("Sorted array:\n");
    printArray(arr, len);
}

void actionSort()
{
    printSortMenu();

    int typeSort = 0;
    scanf("%d", &typeSort);

    if (!(1 <= typeSort && typeSort <= 3))
    {
        printf("No such type of sort!");
        return;
    }

    void *ptrFuncSort;

    if (typeSort == 1)
        ptrFuncSort = bubbleSort;
    else if (typeSort == 2)
        ptrFuncSort = insertionSort;
    else
        ptrFuncSort = selectionSort;

    actionSelectTypeSort(ptrFuncSort);
}

double getTimeSortedIncrease(size_t amountElements, int funcSort(int *, size_t))
{
    int totalTime = 0;
    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
    {
        int *arr = malloc(amountElements * sizeof(int));
        for (size_t i = 0; i < amountElements; ++i)
            arr[i] = (int)i;

        totalTime += funcSort(arr, amountElements);
    }

    return (float)totalTime / AMOUNT_SORTS;
}

double getTimeSortedDecrease(size_t amountElements, int funcSort(int *, size_t))
{
    int totalTime = 0;
    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
    {
        int *arr = malloc(amountElements * sizeof(int));
        for (size_t i = 0; i < amountElements; ++i)
            arr[i] = (int)(amountElements - i);

        totalTime += funcSort(arr, amountElements);
    }

    return (float)totalTime / AMOUNT_SORTS;
}

double getTimeSortedRandom(size_t amountElements, int funcSort(int *, size_t))
{
    int totalTime = 0; time_t t;
    srand((unsigned) time(&t));

    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
    {
        int *arr = malloc(amountElements * sizeof(int));
        for (size_t i = 0; i < amountElements; ++i)
            arr[i] = rand();

        totalTime += funcSort(arr, amountElements);
    }

    return (float)totalTime / AMOUNT_SORTS;
}

void actionCharacteristicsSort()
{
    size_t amountElements = 10;

    char *(sortsNames[3]) = {"Bubble sort", "Selection Sort", "Insertion Sort"};
    int (*(sortsFunc[3])) (int *, size_t) = { &bubbleSort, &selectionSort, &insertionSort };
    for(int i = 0; i < 4; ++i)
    {
        printf("\nAmount elements: %ld\n", amountElements);

        for (int j = 0; j < 3; ++j)
        {
            printf("%s:\n", sortsNames[j]);
            printf("Time sorted-increase array: %lf\n", getTimeSortedIncrease(amountElements, sortsFunc[j]));
            printf("Time sorted-decrease array: %lf\n", getTimeSortedDecrease(amountElements, sortsFunc[j]));
            printf("Time sorted-random array: %lf\n", getTimeSortedRandom(amountElements, sortsFunc[j]));
        }

        amountElements *= 10;
    }
}

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
                actionCharacteristicsSort();
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
