/*
 * Упражнение 2.З. Напишите функцию htol(s), которая преобразует последовательность шестнадцатеричных цифр,
 * начинающуюся с 0х или 0Х, в соответствующее целое. Шестнадцатеричными цифрами являются символы 0…9, а…f,
 * А…F.
 *
 */

#include <stdio.h>
#include <ctype.h>

#define INVALID_VALUE -1

int htol(char str[]);

int main(void) {

    char hex_str[] = "0x14fAB";
    printf("%d\n", htol(hex_str));
    return 0;
}

int htol(char str[]) {

    if (str[0] != '0' && tolower(str[1]) != 'x') {
        return INVALID_VALUE;
    }
    int value = 0, pos = 2;
    while (str[pos] != '\0') {
        if (tolower(str[pos]) >= 'a' && tolower(str[pos]) <= 'f') {
            value *= 16;
            value += tolower(str[pos]) - 'a' + 10;

        } else if (tolower(str[pos]) >= '0' && tolower(str[pos]) <= '9') {
            value *= 16;
            value += tolower(str[pos]) - '0';

        } else {
            printf("error in hex value\n");
            return INVALID_VALUE;
        }
        ++pos;
    }
    return value;
}

