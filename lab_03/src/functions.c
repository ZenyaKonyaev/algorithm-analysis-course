//
// Created by zenya2602 on 26.09.22.
//
#include <stdio.h>
#include "functions.h"
#include "combSort.h"
#include "bucketSort.h"
#include "bitonicSort.h"

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

//8 4 2 9 5 2 9

void actionSelectTypeSort(int funcSort(sortElem *, size_t))
{
    sortElem *arr; size_t len, lenTmp = 0;
    getArrElements(&arr, &len);

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
