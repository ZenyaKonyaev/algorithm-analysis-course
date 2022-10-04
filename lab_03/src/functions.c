//
// Created by zenya2602 on 26.09.22.
//
#include <stdio.h>
#include "functions.h"
#include "combSort.h"
#include "bucketSort.h"
#include "bitonicSort.h"
#include "structs.h"

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

int getArrElements(sortElem **arr, size_t *len)
{
    printf("Enter amount elements:\n");

    int tmp;
    if (scanf("%ld", &tmp) != 1 || tmp < 0)
        return ERROR_SIZE_ARRAY;

    *len = tmp;

    *arr = malloc(*len * sizeof(sortElem));

    printf("Enter elements:\n");
    for (size_t i = 0; i < *len; ++i) {
        sortElem elem = { 0, DEFAULT_C, DEFAULT_D };
        if (scanf("%d", &(elem.val)) != 1)
            return ERROR_INPUT_ELEMENT_ARRAY;
        *((*arr) + i) = elem;
    }

    return EXIT_SUCCESS;
}

void printArray(sortElem *arr, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        printf("%d ", arr[i].val);
    printf("\n");
}

//8 4 2 9 5 2 9

int actionSelectTypeSort(int funcSort(sortElem *, size_t))
{
    sortElem *arr; size_t len, lenTmp = 0;

    int error = 0;
    if ((error = getArrElements(&arr, &len)))
        return error;

    if (funcSort == bucketSort)
        initBuckets(len);
    else if (funcSort == bitonicSort) {
        lenTmp = len;
        expandPowerTwo(&arr, &len);
    }


    funcSort(arr, len);

    if (funcSort == bitonicSort)
        shrinkToLen(&arr, &len, lenTmp);

    printf("Sorted array:\n");
    printArray(arr, len);

    return EXIT_SUCCESS;
}

int actionSort()
{
    printSortMenu();

    int typeSort = 0;
    if (scanf("%d", &typeSort) != 1) {
        return ERROR_INPUT_ACTION;
    }

    if (!(1 <= typeSort && typeSort <= 3))
    {
        printf("No such type of sort!\n");
        return EXIT_SUCCESS;
    }

    void *ptrFuncSort;

    if (typeSort == 1)
        ptrFuncSort = combSort;
    else if (typeSort == 2) {
        ptrFuncSort = bucketSort;
    }
    else
        ptrFuncSort = bitonicSort;

    return actionSelectTypeSort(ptrFuncSort);
}

void printerError(int codeError)
{
    switch (codeError) {
        case ERROR_INPUT_ACTION:
            printf("Error in input action! It must be integer!\n");
            break;
        case ERROR_INPUT_ELEMENT_ARRAY:
            printf("Error in input element array! It must be integer!\n");
            break;
        case ERROR_SIZE_ARRAY:
            printf("Error in input size array! It must be non-negative integer!\n");
            break;
        default:
            printf("Unknown error!\n");
            break;
    }
}

