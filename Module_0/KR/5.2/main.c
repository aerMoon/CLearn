/*
 * Упражнение 5.2. Напишите функцию getfloat — аналог getint для чисел с плавающей точкой. Какой тип будет иметь
 * результирующее значение, выдаваемое функцией getfloat?
 *
 */

#include <stdio.h>
#include <ctype.h>

int getch (void);
void ungetch (int);

/* getfloat: читает следующее целое из ввода в *pn */
int getfloat(double *pn)
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
    // Накапливаем целую часть
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0' ) ;
    *pn *= sign;
    // Накапливаем дробную часть
    if (c == '.') {
        double point = 10.0;
        while (isdigit(c = getch())) {
            *pn = *pn + (c - '0' ) / point;
            point *= 10.0;
        }
    }
    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 100

int main(void) {

    int n, getfloat (double *);
    double array[SIZE];
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    // Самописный вывод
    printf("\nБыли введены следующие цифры:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%g\n", i+1, array[i]);
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
