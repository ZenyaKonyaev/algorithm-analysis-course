#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define AMOUNT_BUCKET 10000
#define INF 100000000
#define DEFAULT_C 'c'
#define DEFAULT_D 2.5
#define INC 1
#define DEC 0

//4 2 9 2 5


typedef struct {
    int val;
    char c;
    double d;
} sortElem;

typedef struct {
    size_t len;
    sortElem *arr;
} bucket;

//для удобного универсального разбиения на функции
bucket *arrB;
size_t nBus;

int comparatorIncrease(const void *elem1, const void *elem2)
{
    const sortElem *a = elem1, *b = elem2;
    return a->val > b->val;
}

int comparatorDecrease(const void *elem1, const void *elem2)
{
    const sortElem *a = elem1, *b = elem2;
    return a->val < b->val;
}

int combSort(sortElem *arr, size_t n)
{
    clock_t timeStart = clock();

    float factor = 1.247f; // оптимальное число для вычисления шага сравнения
    size_t gap = (size_t)(n / factor); //шаг между элементами
    while (gap >= 1) {
        for(size_t i = 0, j = gap; j < n; ++i, ++j)
        {
            if (comparatorIncrease(arr + i, arr + j)) {
                sortElem tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        gap /= factor;
    }

    return clock() - timeStart;
}

void pushBackBucket(bucket *b, sortElem *e)
{
    b->arr[b->len] = *e;
    (b->len)++;
}

int bucketSort(sortElem *arr, size_t n)
{
    clock_t timeStart = clock();
    if (n < 2)
        return clock() - timeStart;

    sortElem min = { INF, DEFAULT_C, DEFAULT_D };
    sortElem max = { -INF, DEFAULT_C, DEFAULT_D };
    for (size_t i = 0; i < n; ++i) {
        if (comparatorIncrease(&max, arr + i))
            max = arr[i];
        if (comparatorIncrease(arr + i, &min))
            min = arr[i];
    }

    double range = (max.val) - min.val;
    double lengthBucket = range / nBus;

    for (size_t i = 0; i < n; ++i) {
        size_t idxBucket = (int)((arr[i].val - min.val) / lengthBucket);
        idxBucket = idxBucket >= nBus ? idxBucket - 1 : idxBucket;
        pushBackBucket(arrB + idxBucket, arr + i);
    }

    for (size_t i = 0; i < nBus; ++i)
        qsort(arrB[i].arr, arrB[i].len, sizeof(sortElem), comparatorIncrease);

    size_t idx = 0;
    for (size_t i = 0; i < nBus; ++i)
        for (size_t j = 0; j < arrB[i].len; ++j)
            arr[idx++] = arrB[i].arr[j];

    return clock() - timeStart;
}
//------------------------------------------------------------------- Bitonic Start

void compare(sortElem *arr, size_t i, size_t j, int d)
{
    if (d == comparatorIncrease(arr + i , arr + j))
    {
        sortElem tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void bitonicConnect(sortElem* arr, size_t lo, size_t n, int d)
{
    if (n < 2)
        return;

    size_t m = n / 2;
    for (size_t i = lo; i < lo + m; ++i)
    {
        compare(arr, i, i + m, d);
    }
    bitonicConnect(arr, lo, m, d);
    bitonicConnect(arr, lo + m, m, d);
}

void bitonicSortRecursive(sortElem *arr, size_t lo, size_t n, int dir)
{
    if (n < 2)
        return;

    size_t m = n / 2;
    bitonicSortRecursive(arr, lo, m, INC);
    bitonicSortRecursive(arr, lo + m, m, DEC);
    bitonicConnect(arr,lo, n, dir);
}

void bitonicSort(T* items, int size)
{
    clock_t timeStart = clock();
    bitonicSortRecursive(items, 0, size, INC);
    clock_t timeEnd = clock();
}


//------------------------------------------------------------------------- Bitonic end
int bitonicSort(sortElem *arr, size_t elem)
{
    makeBitonic(arr, elem);
    clock_t timeStart = clock();
    bitonicSortRecursive(arr, elem);
    return clock() - timeStart;
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
           "1) combSort\n"
           "2) bucketSort\n"
           "3) bitonicSort\n");
}

void getArrElements(sortElem **arr, size_t *len)
{
    printf("Enter amount elements:\n");
    scanf("%ld", len);

    *arr = malloc(*len * sizeof(sortElem));

    printf("Enter elements:\n");
    for (size_t i = 0; i < *len; ++i) {
        sortElem elem = { 0, DEFAULT_C, DEFAULT_D };
        scanf("%d", &(elem.val));
        *((*arr) + i) = elem;
    }


}

void printArray(sortElem *arr, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        printf("%d ", arr[i].val);
    printf("\n");
}

void initBuckets(size_t amountElements)
{
    nBus = nBus == 1 ? 1 : amountElements * 0.5;
    arrB = malloc(sizeof(bucket) * nBus);
    for (size_t i = 0; i < nBus; ++i)
    {
        arrB[i].arr = malloc(amountElements * sizeof(sortElem));
        arrB[i].len = 0;
    }
}

void actionSelectTypeSort(int funcSort(sortElem *, size_t))
{
    sortElem *arr; size_t len;
    getArrElements(&arr, &len);

    if (funcSort == bucketSort)
        initBuckets(len);

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
        ptrFuncSort = combSort;
    else if (typeSort == 2) {
        ptrFuncSort = bucketSort;
    }
    else
        ptrFuncSort = bitonicSort;

    actionSelectTypeSort(ptrFuncSort);
}

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
