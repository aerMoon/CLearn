#ifndef STRARRAY_H
#define STRARRAY_H

/*
 * Динамический массив строк
 * ----
 *      - Выделение памяти на PART_ITEMS элементов
 *      - Проверка есть ли ещё память для элемента, если нет, то добавить для PART_ITEMS элементов
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PART_ITEMS 10


// Массив, массивов строк
static char **items_str;
// Количество элементов в массиве
static int _cur_count_str = 0;
// Количество элементов которые могут поместиться в памяти, после инициализации
static int _mem_count_str = 0;

static int _is_valid_index_str(int index) {
// Проверка корректности индекса элемента

    return (index > -1) && (index < _cur_count_str);
}

static void _init_str(void) {
// Инициализация

    _cur_count_str = 0;
    _mem_count_str = PART_ITEMS;
    items_str = (char**)malloc(sizeof(void*) * _mem_count_str);
    if (!items_str){
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < _mem_count_str; i++) {
        items_str[i] = (char*)malloc(BUFSIZ);
        *items_str[i] = '\0';
    }
}

static void _free_str() {
// Финализация

    for (int i = 0; i < _mem_count_str; i++) {
        free(items_str[i]);
    }
    free(items_str);
}

static int _add_str(char *str) {
// Добавить элемент

    if (_mem_count_str == _cur_count_str) {
        _mem_count_str += PART_ITEMS;
        int new_size = _mem_count_str * sizeof(void*);

        items_str = (char**)realloc(items_str, new_size );
        if (!items_str){
            perror("realloc");
            exit(1);
        }
        for (int i = _cur_count_str; i < _mem_count_str; i++) {
            items_str[i] = (char*)malloc(BUFSIZ);
            *items_str[i] = '\0';
        }
    }
    strcpy(items_str[_cur_count_str++], str);
    return _cur_count_str - 1;
}

static char *_get_str(int index) {
// Прочитать элемент
    return (_is_valid_index_str(index)) ? items_str[index] : 0;
}

static int _del_str(int index) {
// Удалить элемент

    if (_is_valid_index_str(index)) {
        // Уничтожим строку
        free(items_str[index]);
        // Сместим элементы
        for (int i = index; i < (_cur_count_str - 1); i++) {
            items_str[i] = items_str[i + 1];
        }
        // Уменьшим количество элементов
        return --_cur_count_str;
    }
    return -1;
}

static int _count_str(void) {
// Вернуть размер массива
    return _cur_count_str;
}

static void _clear_str(void) {
// Очищаем массив

    for (int i = 0; i < _mem_count_str; i++) {
        *items_str[i] = '\0';
    }
    _cur_count_str = 0;
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
    // Список элементов
    int (*count)(void);
    // Очистить список
    void (*clear)(void);

} TStringArray;

void NewStrArray(TStringArray *array) {
// Инициализация типа объекта

    array->init = &_init_str;
    array->free = &_free_str;
    array->add = &_add_str;
    array->get = &_get_str;
    array->del = &_del_str;
    array->count = &_count_str;
    array->clear = &_clear_str;
    array->init();
}

#endif // STRARRAY_H

