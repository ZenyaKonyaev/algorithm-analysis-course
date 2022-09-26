//
// Created by zenya2602 on 26.09.22.
//

#ifndef SRC_BITONICSORT_H
#define SRC_BITONICSORT_H

#include "structs.h"

void expandPowerTwo(sortElem **arr, size_t *len);
void shrinkToLen(sortElem **arr, size_t *curLen, size_t lenToShrink);
int bitonicSort(sortElem *arr, size_t len);

#endif //SRC_BITONICSORT_H
