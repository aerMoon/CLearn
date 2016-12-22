#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PART_ITEMS 10

typedef struct {

   char *key;
   int value;
} TDynamicItem;

// Массив, массивов строк
static TDynamicItem *items_dyn;
// Количество элементов в массиве
static int _cur_count_dyn = 0;
// Количество элементов которые могут поместиться в памяти, после инициализации
static int _mem_count_dyn = 0;

static int _is_valid_index_dyn(int index) {
// Проверка корректности индекса элемента

    return (index > -1) && (index < _cur_count_dyn);
}

static void _init_dyn(void) {
// Инициализация

    _cur_count_dyn = 0;
    _mem_count_dyn = PART_ITEMS;
    items_dyn = (TDynamicItem*)malloc(_mem_count_dyn * sizeof(TDynamicItem*));
    if (!items_dyn){
        perror("malloc");
        exit(1);
    }
}

static void _free_dyn() {
// Финализация

    for (int i = 0; i < _mem_count_dyn; i++) {
        free(items_dyn[i].key);
    }
    free(items_dyn);
}

static int _add_dyn(char *key, int value) {
// Добавить элемент

    if (_mem_count_dyn == _cur_count_dyn) {
        _mem_count_dyn += PART_ITEMS;
        int new_size = _mem_count_dyn * sizeof(TDynamicItem*);

        items_dyn = (TDynamicItem*)realloc(items_dyn, new_size);
        if (!items_dyn){
            perror("realloc");
            exit(1);
        }
    }
    items_dyn[_cur_count_dyn].key = strdup(key);
    items_dyn[_cur_count_dyn++].value = value;
    return _cur_count_dyn - 1;
}

static int _count_dyn(void) {
// Вернуть размер массива
    return _cur_count_dyn;
}

static TDynamicItem _get_dyn(int index) {
// Вернуть элемент массива

    TDynamicItem zero;
    zero.key = 0;
    zero.value = -1;
    if (_is_valid_index_dyn(index))
        return items_dyn[index];
    else
        return zero;
}

static void _set_dyn(int index, TDynamicItem item) {
// Вернуть элемент массива

    if (_is_valid_index_dyn(index))
        items_dyn[index] = item;
}

static void _swap_dyn(int left, int right) {

    if (_is_valid_index_dyn(left) && _is_valid_index_dyn(right)) {

        TDynamicItem item;
        item = items_dyn[left];
        items_dyn[left] = items_dyn[right];
        items_dyn[right] = item;
    }
}

typedef struct {

    // Конструкторы и деструкторы
    void (*init)(void);
    void (*free)(void);

    // Добавить ключ и значение
    int (*add)(char *key, int value);
    // Прочитать элемент
    TDynamicItem (*get)(int index);
    // Записать элемент
    void (*set)(int index, TDynamicItem item);
    // Размер массива
    int (*count)(void);
    // Поменять местами элементы
    void (*swap)(int left, int right);

} TDynamicArray;

void NewDynArray(TDynamicArray *array) {
// Инициализация типа объекта

    array->init = &_init_dyn;
    array->free = &_free_dyn;
    array->add = &_add_dyn;
    array->get = &_get_dyn;
    array->set = &_set_dyn;
    array->count = &_count_dyn;
    array->swap = &_swap_dyn;
    array->init();
}

#endif // DYNARRAY_H

