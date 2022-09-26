//
// Created by zenya2602 on 26.09.22.
//

#include "bucketSort.h"
#include "time.h"

bucket *arrB;
size_t nBus;

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
