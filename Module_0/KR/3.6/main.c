/*
 * Упражнение 3.6. Напишите версию itoa с дополнительным третьим аргументом, задающим минимальную
 * ширину поля. При необходимости преобразованное число должно слева дополняться пробелами.
 *
 */

#include <stdio.h>
#include <math.h>

void reverse(char buf[], int minwidth) {

    int len = 0;
    while (buf[len] != '\0')
        ++len;
    --len;
    // Добавляем в конец пробелы
    if (len < minwidth) {
        int padding = minwidth - len;
        for (int i = len + 1; i < len + padding; i++)
            buf[i] = ' ';
        len += padding;
        buf[len--] = '\0';
    }
    // Разворачиваем не трогая пробелы
    for (int i = 0; len > i; i++, len--) {
        int ch = buf[i];
        buf[i] = buf[len];
        buf[len] = ch;
    }
}

/* itoa: преобразование n в строку s */
void itoa (int n, char s[], int minwidth)
{
    int i, sign;
    if ((sign = n) < 0) /* сохраняем знак */
        n = abs(n - 1); /* делаем n положительным */
    i = 0;
    do { /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0'; /* следующая цифра */
    } while ((n /= 10) > 0); /* исключить ее */
    if (sign < 0) {
        s[0] += 1;
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s, minwidth);
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
    itoa(12345, buf, 8);
    print(buf);
    return 0;
}
