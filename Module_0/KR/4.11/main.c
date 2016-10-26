/*
 * Упражнение 4.11. Модифицируйте функцию getop так, чтобы отпала необходимость в функции ungetch.
 * Подсказка: используйте внутреннюю статическую переменную.
 *
 * p.s. Использовал для основы 4.9 т.к. в 4.10 выпил ungetch и вырезал добавления...
 *
 */

#include <stdio.h>
#include <stdlib.h> /* для atof() */
#include <ctype.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100 /* макс. размер операнда или оператора */
#define MAXVAL 100 /* максимальная глубина стека */


char fungets = false; /* флаг того, что мы вернули в буфер данные */

int strequ(char s1[], char s2[], int len);
void ungets(char s[]);

/* калькулятор с обратной польской записью */
int main(void)
{
    int type;
    double op1, op2;
    char s[MAXOP];
    while ((type = getop (s)) != EOF) {
        switch (type) {
            case NUMBER:
                push (atof (s));
                break;            
            case '%':
                op2 = pop();
                if (op2 != 0.0) {
                    op1 = pop();
                    push( op1 - op2 * (int)(op1 / op2) );
                }
                else
                    printf("ошибка: деление на нуль\n");
                break;
            case '+':
                push (pop() + pop());
                break;
            case '*':
                push (pop() * pop());
                break;
            case '-':
                op2 = pop();
                push (pop() - op2);
                break;
            case '/' :
                op2 = pop();
                if (op2 != 0.0)
                    push (pop() / op2);
                else
                    printf("ошибка: деление на нуль\n");
                break;
            case '\n' :
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("ошибка: неизвестная операция %s\n", s);
                break;
        }
    }
    printf("получен EOF\n");
    return 0;
}

// Возвращает строку s во входной поток
void ungets(char s[]) {

    // Узнаём размер
    int pos;
    for (pos = 0; s[pos] != '\0' && s[pos] != '\n' && s[pos] != EOF; pos++)
        ;
    --pos;

    // Возвращаем с конца в буфер
    while (pos >= 0) {
        ungetch(s[pos]);
        --pos;
    }
}

// Сравнить строки, 0 не равны, 1 равны
int strequ(char s1[], char s2[], int len) {

    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}
