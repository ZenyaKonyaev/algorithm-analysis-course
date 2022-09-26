//
// Created by zenya2602 on 26.09.22.
//

#include "structs.h"

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
