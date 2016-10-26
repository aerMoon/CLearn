/*
 * Упражнение 2.10. Напишите функцию lower, которая переводит большие буквы в малые, используя
 * условное выражение (а не конструкцию if-else).
 *
 */

#include <stdio.h>

/* lower: преобразование с в строчную; только для ASCII */
int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main(void) {

    char text[] = "HELLO WORLD!!!";
    for (int i = 0; text[i] != '\0'; i++)
        putchar(lower(text[i]));
    putchar('\n');
    return 0;
}
