#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char **strings;
static int stack_cnt;
static int stack_pos = 0;

static void stack_init(int count) {
// Инициализация стека

    strings = (char**)malloc(sizeof(void) * count);
    for (int i = 0; i < count; i++) {
        strings[i] = (char*)malloc(BUFSIZ);
        *strings[i] = '\0';
    }
    stack_cnt = count;
}

static void stack_free() {
// Финализация стека

    for (int i = 0; i < stack_cnt; i++) {
        free(strings[i]);
    }
}

static int stack_push(char *str) {

    if (stack_pos < 0 || stack_pos == stack_cnt) {
        stack_pos = 0;
    }
    strcpy(strings[stack_pos++], str);
    return stack_pos;
}

static int stack_pop(char *str) {

    if (stack_pos < 0) {
        return 0;
    }
    strcpy(str, strings[--stack_pos]);
    return stack_pos;
}

static int stack_count(void) {

    return stack_pos + 1;
}


typedef struct {
// Закос под объекты

    void (*init)(int count);
    void (*free)(void);

    int (*push)(char *str);
    int (*pop)(char *str);
    int (*count)(void);
} TStrStack;

void InitStrStack(TStrStack *stack) {
// Инициализация типа объекта

    stack->init = &stack_init;
    stack->free = &stack_free;

    stack->push = &stack_push;
    stack->pop = &stack_pop;
    stack->count = &stack_count;
}

#endif // STACK_H

