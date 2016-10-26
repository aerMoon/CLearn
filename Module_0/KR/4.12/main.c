/*
 * Упражнение 4.12. Примените идеи, которые мы использовали в рrintd, для написания рекурсивной версии функции itoa;
 * иначе говоря, преобразуйте целое число в строку цифр с помощью рекурсивной программы.
 *
 */

#include <stdio.h>

void itoa(int n, char s[])
{
    static int pos = 0;
    if (n < 0) {
        s[pos++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    s[pos++] = n % 10 + '0';
    s[pos] = 0;
}

void print(char text[])
{
    int pos = 0;
    while (text[pos] != 0) {
        putchar(text[pos]);
        ++pos;
    }
    putchar('\n');
}

int main(void)
{
    char buf[BUFSIZ];
    itoa(130492, buf);
    print(buf);
    return 0;
}
