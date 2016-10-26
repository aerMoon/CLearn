/*
 * Упражнение 1.19. Напишите функцию reverse(s), размещающую символы в строке s в обратном порядке.
 * Примените ее при написании программы, которая каждую вводимую строку располагает в обратном порядке.
 *
 */

#include <stdio.h>

#define MAX_LEN 1024

void clearBuf(int buf[], int len);
int getLine(int outBuf[], int maxLen);
void reverse (int inBuf[], int outBuf[], int len);
void print(int buf[], int len);

int main(void) {

    int inBuf[MAX_LEN];
    int outBuf[MAX_LEN];
    int len;

    clearBuf(inBuf, MAX_LEN);
    clearBuf(outBuf, MAX_LEN);

    while ((len = getLine(inBuf, MAX_LEN)) != 0) {

        printf("entered: %d char[s]\n", len);
        reverse(inBuf, outBuf, len);
        printf("reverse: ");
        print(outBuf, len);
        printf("\n");

        clearBuf(inBuf, MAX_LEN);
        clearBuf(outBuf, MAX_LEN);
    }
    return 0;
}

void print(int buf[], int len) {

    for (int i = 0; i < len; i++) {
        putchar(buf[i]);
    }
}

void clearBuf(int buf[], int len) {

    // Очищает буфер

    for (int i = 0; i < len; i++) {
        buf[i] = 0;
    }
}

int getLine(int outBuf[], int maxLen) {

    // Получает строку из стандартного потока ввода

    int ch, pos = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n')
            break;
        outBuf[pos] = ch;
        ++pos;
        if (pos > maxLen) {
            --pos;
            break;
        }
    }
    return pos;
}


void reverse(int inBuf[], int outBuf[], int len) {

    int revpos = 0;
    for (int i = --len; i > -1; i--) {
        outBuf[revpos] = inBuf[i];
        ++revpos;
    }
}
