//
// Created by zenya2602 on 26.09.22.
//

#include "bitonicSort.h"
#include "time.h"
#include "math.h"
#include "stdlib.h"

#define INC 1
#define DEC 0
#define EPS 1e-7

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

void expandPowerTwo(sortElem **arr, size_t *len)
{
    double resD = log2(*len);
    int resI = log2(*len);

    if (fabs(resD - resI) < EPS)
        return;

    size_t newLen = pow(2, resI + 1);

    sortElem *newArr = malloc(sizeof(sortElem) * (newLen));

    for (size_t i = 0; i < *len; ++i)
        newArr[i] = (*arr)[i];

    sortElem expandedElem = { INF, DEFAULT_C, DEFAULT_D };
    for (size_t i = *len; i < newLen; ++i)
        newArr[i] = expandedElem;

    free(*arr);
    *arr = newArr;
    *len = newLen;
}

void shrinkToLen(sortElem **arr, size_t *curLen, size_t lenToShrink)
{
    if (*curLen <= lenToShrink)
        return;

    sortElem *newArr = malloc(sizeof(sortElem) * lenToShrink);
    for (size_t i = 0; i < lenToShrink; ++i)
        newArr[i] = (*arr)[i];

    free(*arr);
    *arr = newArr;
    *curLen = lenToShrink;
}

int bitonicSort(sortElem *arr, size_t len)
{
    clock_t timeStart = clock();
    bitonicSortRecursive(arr, 0, len, INC);

    return clock() - timeStart;
}
