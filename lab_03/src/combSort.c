//
// Created by zenya2602 on 26.09.22.
//

#include "combSort.h"
#include "time.h"


//4 2 9 1 6
int combSort(sortElem *arr, size_t n)
{
    clock_t timeStart = clock();

    float factor = 1.247f; // оптимальное число для вычисления шага сравнения
    size_t gap = (size_t)(n / factor); //шаг между элементами
    int swapped = 1;
    while (gap != 1 || swapped) {
        swapped = 0;
        for(size_t i = 0, j = gap; j < n; ++i, ++j)
        {
            if (comparatorIncrease(arr + i, arr + j)) {
                sortElem tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                swapped = 1;
            }
        }
        gap = gap / factor < 1 ? 1 : gap / factor;
    }

    return clock() - timeStart;
}
