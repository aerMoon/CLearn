/*
 * Упражнение 5.4. Напишите функцию strend(s, t), которая выдает 1, если строка t расположена в конце строки s,
 * и нуль в противном случае.
 *
 */

#include <stdio.h>
#include <stdlib.h>


int strend(char *s, char *t)
{
    // Получим длину s
    int len_s = 0;
    while (*s++)
        ++len_s;
    --s;

    // Получим длину t
    int len_t = 0;
    while (*t++)
        ++len_t;
    --t;

    // Идём от конца s
    while (len_t-- && len_s--) {
        if (*s-- != *t--)
            return 0;
    }
    return 1;
}

int main(void) {

    char *s = "Hello World!";
    char *t = "World!";
    printf("%d\n", strend(s, t));
    return 0;
}
