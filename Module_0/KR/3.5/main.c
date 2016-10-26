/*
 * Упражнение 3.5. Напишите функцию itob(n, s, b), которая переводит целое n в строку s,
 * представляющую число по основанию b. В частности, itob(n, s, 16) помещает в s текст
 * числа n в шестнадцатеричном виде.
 *
 */

#include <stdio.h>

void reverse(char buf[]) {
    int len = 0;
    while (buf[len] != '\0')
        ++len;
    --len;
    for (int i = 0; len > i; i++, len--) {
        int ch = buf[i];
        buf[i] = buf[len];
        buf[len] = ch;
    }
}

void itob(int n, char s[], int b) {
    const char alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int pos = 0;
    do {
        s[pos++] = alphabet[n % b];
        n /= b;
    } while (n >= b);
    s[pos++] = alphabet[n];
    s[pos++] = '\0';
    reverse(s);
}

void print(char text[]) {
    int pos = 0;
    while (text[pos] != '\0') {
        putchar(text[pos]);
        ++pos;
    }
    putchar('\n');
}

int main(void) {

    char buf[1024];
    itob(124, buf, 2);
    printf("Переводим десятичное 124 в двоичную систему счисления: ");
    print(buf);
    printf("Переводим десятичное 124 в шестнадцатиричную систему счисления: ");
    itob(124, buf, 16);
    print(buf);
    return 0;
}
