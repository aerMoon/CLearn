/*
 * Упражнение 5.6. Отберите подходящие программы из предыдущих глав и упражнений и перепишите их, используя вместо
 * индексирования указатели. Подойдут, в частности, программы getline (главы 1 и 4), atoi, itoa и их варианты
 * (главы 2, 3 и 4), reverse (глава 3), а также strindex и getop (глава 4).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define NUMBER '0' /* признак числа */
#define false 0
#define true !false

char buf[BUFSIZ]; /* буфер для ungetch */
int bufp = 0; /* след, свободная позиция в буфере */

int getline(char *text, int maxlen) {

    int ch, pos = 0;
    while ((ch = getchar()) != EOF && pos < maxlen) {
        if (ch == '\n') {
            break;
        }
        text[pos] = ch;
        ++pos;
    }
    text[pos] = 0;
    return --pos;
}

void itoa_my(int n, char *s)
{
    static int pos = 0;
    if (n < 0) {
        s[pos++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa_my(n / 10, s);
    s[pos++] = n % 10 + '0';
    s[pos] = 0;
}

/* atof: преобразование строки s в double */
double myatof (char *s) // Стандарт 11 не позволяет перекрывать так имена ибо atof есть в math.h
{
    double val, power;
    int i, sign;
    for (i = 0; isspace (s[i]); i++)
        ; /* игнорирование левых символов-разделителей */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit (s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] =='.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    // Устанавливаем степень числа через е
    int powerDig = 0;
    if (tolower(s[i]) == 'e') {
        int powerSing = true;
        ++i;
        if (s[i] == '-') {
            powerSing = false;
            ++i;
        } else if (s[i] == '+') {
            ++i;
        }
        while (isdigit(s[i])) {
            powerDig *= 10;
            if (powerSing) {
                powerDig += s[i] - '0';
            } else {
                powerDig -= s[i] - '0';
            }
            ++i;
        }
    }
    return sign * val / power * pow(10, powerDig);
}

void reverse(char *buf) {

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

int strindex(char *s, char *t) {

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

int getch(void) /* взять (возможно возвращенный) символ */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* вернуть символ на ввод */
{
    if (bufp >= BUFSIZ)
        printf ("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}

/* getop: получает следующий оператор или операнд */
int getop(char *s)
{
    int i = 0, c;
    while ((c = getch()) == ' ' || c == '\t' )
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        if (c == '-') {
            s[i++] = c;
            if (!isdigit(c = getch())) {
                ungetch(c);
                return s[--i]; /* не число */
            }
        } else {
            return c; /* не число */
        }
    }

    /* накапливаем целую часть */
    if (isdigit(c)) {
        s[i++] = c;
        while (isdigit(s[i++] = c = getch()))
            ;
    }

    /* накапливаем дробную часть */
    if (c == '.') {
        s[i++] = c;
        while (isdigit(s[i++] = c = getch()))
            ;
    }
    if (!isdigit(s[i - 1]))
        --i;
    if (c != EOF)
        ungetch(c);
    s[i] = '\0';
    return NUMBER;
}


int main(void) {

    char *pbuf = malloc(BUFSIZ);

    // itoa_my - переведём десятичное 126 в строку
    itoa_my(1234567890, pbuf);
    printf(pbuf);
    putchar('\n');

    // strindex - выдает позицию самого правого вхождения t в s
    printf("Позиция '890' в строке: %d\n", strindex(pbuf, "890"));

    // getline - прочитаем строку
    getline(pbuf, 15);
    printf(pbuf);
    putchar('\n');

    // reverse - перевернём строку
    reverse(pbuf);
    printf(pbuf);
    putchar('\n');

    // myatof - попробуем строку преобразовать в число
    printf("%g\n", myatof("194.3465"));

    // getop - штукенция для определния типа вводимых данных
    printf("return: %d\npbuf: ", getop(pbuf));
    printf(pbuf);
    putchar('\n');

    free(pbuf);
    return 0;    
}
