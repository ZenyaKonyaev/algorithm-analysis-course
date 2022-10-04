//
// Created by zenya2602 on 26.09.22.
//

#ifndef SRC_STRUCTS_H
#define SRC_STRUCTS_H

#include <stdlib.h>

#define INF 100000000
#define DEFAULT_C 'c'
#define DEFAULT_D 2.5

// ERRORS

#define ERROR_INPUT_ACTION 1
#define ERROR_SIZE_ARRAY 2
#define ERROR_INPUT_ELEMENT_ARRAY 3

typedef struct {
    int val;
    char c;
    double d;
} sortElem;

typedef struct {
    size_t len;
    sortElem *arr;
} bucket;

int comparatorIncrease(const void *elem1, const void *elem2);
int comparatorDecrease(const void *elem1, const void *elem2);

#endif //SRC_STRUCTS_H
