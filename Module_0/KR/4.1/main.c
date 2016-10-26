/*
 * Упражнение 4.1. Напишите функцию strindex(s, t), которая выдает позицию самого правого вхождения
 * t в s или -1, если вхождения не обнаружено.
 *
 */

#include <stdio.h>

int strindex(char s[], char t[]) {

    // Вычисляем длины строк
    int len_s = 0;
    while (s[len_s] != 0)
        ++len_s;
    int len_t = 0;
    while (t[len_t] != 0)
        ++len_t;

    // Ищем вхождения
    for (int i = len_s - len_t; i >= 0; i--) {
        int pos = 0;
        if (s[i] == t[pos]) {
            while (t[pos] != 0) {
                if (s[i + pos] != t[pos]) {
                    goto nofound;
                }
                ++pos;
            }
            return i; // found
        }
        nofound:
            continue;
    }
    return -1;
}

int main(void) {

    printf("Ищем Hello в фразе Hello World! Позиция: %d\n", strindex("Hello World!", "Hello"));
    printf("Ищем World в фразе Hello World! Позиция: %d\n", strindex("Hello World!", "World"));
    return 0;
}
