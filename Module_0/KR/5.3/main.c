/*
 * Упражнение 5.3. Используя указатели, напишите функцию strcat, которую мы рассматривали в главе 2 (функция
 * strcat(s, t) копирует строку t в конец строки s).
 *
 */

#include <stdio.h>
#include <stdlib.h>

void strcat_my(char *s, char *t)
{
    char *p;
    p = s;
    while (*p++) /* находим конец s */
        ;
    --p;
    while ((*p++ = *t++)) /* копируем t */
        ;
}

/* strcpy: копирует t в s; версия 3 (с указателями) */
void strcpy_my(char *s, char *t)
{
    while ((*s++ = *t++))
        ;
}

int main(void) {

    char *s = malloc(100);
    char *t = "World!\n";
    strcpy_my(s, "Hello ");
    strcat_my(s, t);
    printf(s);
    free(s);
    return 0;
}
