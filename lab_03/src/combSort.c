//
// Created by zenya2602 on 26.09.22.
//

#include "combSort.h"
#include "time.h"

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
