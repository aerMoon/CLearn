/*
 * Упражнение 4.14. Определите swap(t, x, y) в виде макроса, который осуществляет обмен значениями указанного типа
 * t между аргументами x и y. (Примените блочную структуру.)
 *
 */

#include <stdio.h>

#define kr_swap(t, x, y) {t temp; temp = x; x = y; y = temp;}

int main(void) {

    int x = 10;
    int y = 20;
    printf("x = %d\ny = %d\n\n", x, y);
    kr_swap(int, x, y);
    printf("x = %d\ny = %d\n\n", x, y);
    return 0;
}
