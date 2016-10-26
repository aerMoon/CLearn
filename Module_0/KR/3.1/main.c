/*
 * Упражнение 3.1. В нашей программе бинарного поиска внутри цикла осуществляются две проверки, хотя
 * могла быть только одна (при увеличении числа проверок вне цикла). Напишите программу, предусмотрев в
 * ней одну проверку внутри цикла. Оцените разницу во времени выполнения.
 *
 */

#include <stdio.h>

/* binsearch: найти х в v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 2 ;
    mid = (low+high) / 2;
    while ( low <= high && x != v[mid] ) {
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1 ;
        mid = (low + high) / 2;
    }
    if (x == v[mid])
        return mid;
    else
            return -1; /* совпадения нет */
}

#define COUNT 1000

int main(void) {

    int test[COUNT + 1];
    for (int i = 0; i <= COUNT; i++) {
        test[i] = i;
    }

    printf("Позиция 400 в массиве: %d\n", binsearch(400, test, COUNT + 1));
    return 0;
}
