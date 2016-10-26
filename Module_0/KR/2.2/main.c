/*
 * Упражнение 2.2. Напишите цикл, эквивалентный приведенному выше fоr-циклу, не пользуясь операторами
 * && и ||.
 *
 */

#include <stdio.h>

#define MAX_LEN 1024

int main(void) {

    int i, c;
    int lim = MAX_LEN;
    int s[MAX_LEN];

    for (i = 0; (i < lim - 1) == ((c = getchar()) != EOF) == (c != '\n'); ++i)
        s[i] = c;

    return 0;
}
