//
// Created by zenya2602 on 26.09.22.
//

#include <stdio.h>
#include <time.h>

#include "timeCounter.h"
#include "bitonicSort.h"
#include "bucketSort.h"
#include "combSort.h"

#define AMOUNT_SORTS 100

double getTimeSortedIncrease(size_t amountElements, int funcSort(sortElem *, size_t))
{
    int totalTime = 0;
    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
    {

        sortElem *arr = malloc(amountElements * sizeof(sortElem));

        for (size_t i = 0; i < amountElements; ++i) {
            sortElem t = { (int)i, DEFAULT_C, DEFAULT_D};
            arr[i] = t;
        }

        size_t lenTmp = 0;
        if (funcSort == bucketSort)
            initBuckets(amountElements);
        else if (funcSort == bitonicSort) {
            lenTmp = amountElements;
            expandPowerTwo(&arr, &amountElements);
        }

        totalTime += funcSort(arr, amountElements);

        if (funcSort == bitonicSort)
            shrinkToLen(&arr, &amountElements, lenTmp);

        free(arr);
    }

    return (float)totalTime / AMOUNT_SORTS;
}

double getTimeSortedDecrease(size_t amountElements, int funcSort(sortElem *, size_t))
{
    int totalTime = 0;
    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
    {
        sortElem *arr = malloc(amountElements * sizeof(sortElem));
        for (size_t i = 0; i < amountElements; ++i) {
            sortElem t = { amountElements - i, DEFAULT_C, DEFAULT_D };
            arr[i] = t;
        }


        size_t lenTmp = 0;
        if (funcSort == bucketSort)
            initBuckets(amountElements);
        else if (funcSort == bitonicSort) {
            lenTmp = amountElements;
            expandPowerTwo(&arr, &amountElements);
        }

        totalTime += funcSort(arr, amountElements);

        if (funcSort == bitonicSort)
            shrinkToLen(&arr, &amountElements, lenTmp);
        free(arr);
    }

    return (float)totalTime / AMOUNT_SORTS;
}

double getTimeSortedRandom(size_t amountElements, int funcSort(sortElem *, size_t), int maxNum)
{
    int totalTime = 0; time_t t;
    srand((unsigned) time(&t));

    for (int iteration = 0; iteration < AMOUNT_SORTS; ++iteration)
    {

        sortElem *arr = malloc(amountElements * sizeof(sortElem));
        for (size_t i = 0; i < amountElements; ++i) {
            sortElem tmpElem = { rand() % (maxNum + 1), DEFAULT_C, DEFAULT_D };
            arr[i] = tmpElem;
        }

        size_t lenTmp = 0;
        if (funcSort == bucketSort)
            initBuckets(amountElements);
        else if (funcSort == bitonicSort) {
            lenTmp = amountElements;
            expandPowerTwo(&arr, &amountElements);
        }

        totalTime += funcSort(arr, amountElements);

        if (funcSort == bitonicSort)
            shrinkToLen(&arr, &amountElements, lenTmp);
        free(arr);
    }

    return (float)totalTime / AMOUNT_SORTS;
}

void actionCharacteristicsSort()
{
    int widthNumbers[3] = { 1000, 3, 10000};

    size_t amountElements = 10;

    char *(sortsNames[3]) = {"combSort", "bucketSort", "bitonicSort"};
    int (*(sortsFunc[3])) (sortElem *, size_t) = { &combSort, &bucketSort, &bitonicSort };
    for(int i = 0; i < 4; ++i)
    {
        printf("\nAmount elements: %ld\n", amountElements);

        for (int j = 0; j < 3; ++j)
        {
                printf("%s:\n", sortsNames[j]);
                printf("Time sorted-increase array: %lf\n", getTimeSortedIncrease(amountElements, sortsFunc[j]));
                printf("Time sorted-decrease array: %lf\n", getTimeSortedDecrease(amountElements, sortsFunc[j]));
                for (int k = 0; k < 3; ++k) {
                    printf("Time sorted-random array (numbers from 0 to %d): %lf\n", widthNumbers[k],
                           getTimeSortedRandom(amountElements, sortsFunc[j], widthNumbers[k]));
                }
                printf("\n");
        }
        printf("\n--------\n\n");

        amountElements *= 10;
    }
}


