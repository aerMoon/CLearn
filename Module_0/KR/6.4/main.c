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

TDynamicArray array;

int getline(char outBuf[]);
void append(char *keyBuf);

int main(void) {

    // Создаём массив
    NewDynArray(&array);

    // Читаем текст
    int len;
    char inBuf[BUFSIZ];
    while ((len = getline(inBuf)) != 0) {
        append(inBuf);
    }

    // Соритировка в порядке возрастания - это значит редкие сначала
    for (int i = 0; i < array.count() - 1; i++) {
        for (int j = 0; j < array.count() - 1; j++) {
            if (array.get(j).value > array.get(j + 1).value) {
                array.swap(j, j + 1);
            }
        }
    }

    // Печатаем элементы
    for (int i = 0; i < array.count(); i++) {
        TDynamicItem item = array.get(i);
        printf("%d - %s\n", item.value, item.key);
    }

    // Уничтожаем массив
    array.free();

    return 0;
}

void append(char *keyBuf) {

    // Ищем элемент
    int flag = 0;
    for (int i = 0; i < array.count(); i++) {
        if (strcmp(array.get(i).key, keyBuf) == 0) {
            flag = 1;
            TDynamicItem item = array.get(i);
            item.value += 1;
            array.set(i, item);
        }
    }
    if (!flag) {
        array.add(keyBuf, 1);
    }
}

int getline(char outBuf[]) {
    // Получить строку
    int ch, pos = 0;
    while ((ch = getchar()) != EOF) {
        if ((ch == '\n') || (pos > BUFSIZ))
            break;
        outBuf[pos] = ch;
        ++pos;
    }
    outBuf[pos] = '\0';
    return pos;
}

