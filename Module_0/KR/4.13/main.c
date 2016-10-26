/*
 * Упражнение 4.13. Напишите рекурсивную версию функции reverse(s), переставляющую элементы строки в ту же
 * строку в обратном порядке.
 *
 */

#include <stdio.h>

void reverse(char buf[]) {

    static int pos = 0;
    static int len = EOF;
    int curr = pos;
    ++pos;
    if (buf[curr] != '\0') {
        reverse(buf);
    } else {
        len = curr;
    }
    if (len != EOF) {

        int mirror = len - curr - 1;
        if (mirror >= len / 2){
            if (mirror + 1) {
                char ch_swap = buf[mirror];
                buf[mirror] = buf[curr];
                buf[curr] = ch_swap;
            }
        }
    }
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

int main(void) {

    char buf[] = "!dlroW olleH";
    reverse(buf);
    print(buf);
    return 0;
}
