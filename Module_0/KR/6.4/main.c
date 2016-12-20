/*
 * Упражнение 6.4. Напишите программу, которая печатает весь набор различных слов, образующих входной поток, в порядке
 * возрастания частоты их встречаемости. Перед каждым словом должно быть указано число вхождений.
 *
 * p.s. сделаю так как хочу (=
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "dynarray.h"

TStrArray array;

int main(void) {

    NewStrArray(&array);

    array.init();
    array.add("hello");
    array.add("world");
    array.add("bitch");

    for (int i = 0; i < 3; i++) {
        printf(array.get(i));
        putchar('\n');
    }

    array.free();

    return 0;
}
