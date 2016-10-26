/*
 * Упражнение 5.1. Функция getint написана так, что знаки - или +, за которыми не следует цифра, она понимает как
 * "правильное" представление нуля. Скорректируйте программу таким образом, чтобы в подобных случаях она возвращала
 * прочитанный знак назад во ввод.
 *
 */

#include <stdio.h>
#include <ctype.h>

int getch (void);
void ungetch (int);

/* getint: читает следующее целое из ввода в *pn */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch()))
        ; /* пропуск символов-разделителей */
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' ) {
        // ungetch(c); /* не число */
        return 0;
    }
    sign = ( c == '-' ) ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(sign == 1 ? '+' : '-');
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0' ) ;
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 100

int main(void) {

    // Ввод по учебнику
    int n, array[SIZE], getint (int *);
    for (n = 0; n < SIZE && getint (&array[n]) != EOF; n++)
        ;

    // Самописный вывод
    printf("\nБыли введены следующие цифры:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", i+1, array[i]);
    }
    return 0;
}

static char buf [BUFSIZ];
static int bufp = 0;

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
