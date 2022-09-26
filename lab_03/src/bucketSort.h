//
// Created by zenya2602 on 26.09.22.
//

#ifndef SRC_BUCKETSORT_H
#define SRC_BUCKETSORT_H

#include "structs.h"

//для удобного универсального разбиения на функции

void pushBackBucket(bucket *b, sortElem *e);
int bucketSort(sortElem *arr, size_t n);
void initBuckets(size_t amountElements);

#endif //SRC_BUCKETSORT_H
