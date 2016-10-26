#include <stdio.h>
#include <ctype.h>
#include "calc.h"

static int lastch = EOF;

/* getop: получает следующий оператор или операнд */
int getop(char s[])
{
    int i = 0, c;
    if (lastch == EOF || lastch == ' ') {
        while ((c = getch()) == ' ' || c == '\t' )
            ;
    } else {
        c = lastch;
        lastch = EOF;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        if (c == '-') {
            s[i++] = c;
            if (!isdigit(c = getch())) {
                //ungetch(c);
                lastch = c;
                return s[--i]; /* не число */
            }
        } else {
            if (c == EOF)
                return EOF;
            return c; /* не число и не переменная */
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
    if (c != EOF) {
        //ungetch(c);
        lastch = c;
    }
    s[i] = '\0';
    return NUMBER;
}
