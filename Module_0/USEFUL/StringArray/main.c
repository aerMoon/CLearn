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
#include "strarray.h"

TStringArray array;

int main(void) {

    // Создаём массив
    NewStrArray(&array);

    // Инициализируем
    array.add("hello");
    array.add("world");
    array.add("bitch");

    // Печатаем элементы
    for (int i = 0; i < array.count(); i++) {
        printf(array.get(i));
        putchar('\n');
    }

    // Удаляем 2-й элемент
    array.del(1);
    putchar('\n');

    // Печатаем элементы массива
    for (int i = 0; i < array.count(); i++) {
        printf(array.get(i));
        putchar('\n');
    }

    //  Очищаем массив
    array.clear();

    // Печатаем элементы массива
    for (int i = 0; i < array.count(); i++) {
        printf(array.get(i));
        putchar('\n');
    }

    // Уничтожаем массив
    array.free();

    return 0;
}
