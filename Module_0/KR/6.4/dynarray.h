#ifndef DYNARRAY_H
#define DYNARRAY_H

/*
 * Динамический массив строк
 * ----
 * На данный момент в этом модуле будет реализация только динамического массива СТРОК.
 *
 * ИНИЦИАЛИЗАЦИЯ:
 *      - Выделение памяти на PART_ITEMS элементов
 *
 * ДОБАВЛЕНИЕ НОВОГО ЭЛЕМЕНТА:
 *      - Проверка есть ли ещё память для элемента, если нет, то добавить для PART_ITEMS элементов
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PART_ITEMS 100

// Массив, массивов строк
static char **strings;
// Количество элементов в массиве
static int _count = 0;
// Количество элементов которые могут поместиться в памяти, после инициализации
static int _mem_count = 0;

static void _init(void) {
// Инициализация

    _count = 0;
    _mem_count = PART_ITEMS;
    strings = (char**)malloc(sizeof(void*) * PART_ITEMS);
    for (int i = 0; i < _mem_count; i++) {
        strings[i] = (char*)malloc(BUFSIZ);
        *strings[i] = '\0';
    }
}

static void _free() {
// Финализация

    for (int i = 0; i < _count; i++) {
        free(strings[i]);
    }
    free(strings);
}

static int _add(char *str) {
// Добавить элемент

    if (_mem_count < _count) {
        strcpy(strings[_count++], str);
        strings = (char**)realloc(strings, sizeof(void*) * _count + PART_ITEMS);
    } else {
        strcpy(strings[_count++], str);
    }
    return _count - 1;
}

static char *_get(int index) {
    return strings[index];
}

typedef struct {

    // Конструкторы и деструкторы
    void (*init)(void);
    void (*free)(void);

    // Добавить строку
    int (*add)(char *str);
    // Прочитать строку
    char *(*get)(int index);
    // Удалить строку
    int (*del)(int index);
    // Очистить список
    void (*clear)(void);

} TStrArray;

void NewStrArray(TStrArray *array) {
// Инициализация типа объекта

    array->init = &_init;
    array->free = &_free;
    array->add = &_add;
    array->get = &_get;
}

#endif // DYNARRAY_H

