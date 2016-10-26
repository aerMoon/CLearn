/*
 * Упражнение 4.9. В наших функциях не предусмотрена возможность возврата EOF. Подумайте, что надо сделать, чтобы
 * можно было возвращать EOF, и скорректируйте соответственно программу.
 *
 * p.s. Ну подумал, ну печатаю, что получил EOF и что?!
 *
 */

#include <stdio.h>
#include <stdlib.h> /* для atof() */
#include <ctype.h>
#include <math.h>

#define false 0
#define true !false
#define MAXOP 100 /* макс. размер операнда или оператора */
#define NUMBER '0' /* признак числа */
#define OPERAT '1' /* признак операции */
#define VARIABLE '2' /* признак новой переменной */
#define MAXVAL 100 /* максимальная глубина стека */
#define BUFSIZE 100
#define CALPHABET 26 /* Рарзмер алфавита */

struct rectVar{
    char name;
    double value;
    char isInit;
};

char buf[BUFSIZE]; /* буфер для ungetch */
int bufp = 0; /* след, свободная позиция в буфере */
int sp = 0; /* следующая свободная позиция в стеке */
double val[ MAXVAL ]; /* стек */
struct rectVar var[ CALPHABET ]; /* переменные */
struct rectVar lastVar; /* последняя добавленная переменная */
char fungets = false; /* флаг того, что мы вернули в буфер данные */

int getch(void);
void ungetch(int);
int getop (char []);
void push (double);
double pop (void);
double top (void);
void clonetop (void);
void xchg (void);
void clear (void);
int strequ(char s1[], char s2[], int len);
void ungets(char s[]);

/* калькулятор с обратной польской записью */
int main(void)
{
    int type;
    double op1, op2;
    char s[MAXOP];
    for (int i = 0; i < CALPHABET; i++)
        var[i].isInit = false;
    while ((type = getop (s)) != EOF) {
        switch (type) {
            case NUMBER:
                push (atof (s));
                break;
            case OPERAT:
                // определить операцию
                if (strequ(s, "sin", 3)) {
                    push( sin( pop() ) );
                    break;
                } else if (strequ(s, "exp", 3)) {
                    push( exp( pop() ) );
                    break;
                } else if (strequ(s, "pow", 3)) {
                    push( pow(pop(), pop()));
                    break;
                }else if (strequ(s, "ungets", 6)) {
                    if (!fungets) {
                        ungets(s);
                    } else {
                        printf("Данные были возвращены в стандартный поток в\\в\n");
                    }
                    fungets = !fungets;
                    break;
                }
                printf("ошибка: неизвестная операция %s\n", s);
                break;
            case VARIABLE:
                printf("добавлена переменная: ");
                putchar(lastVar.name);
                printf("=%.8g\n", lastVar.value);
                break;
            case '!': // Печатаем верхний элемент стека
                printf("\ttop> %.8g\n", top());
                break;
            case '@': // Дублируем верхний элемент стека
                clonetop();
                break;
            case '#': // Меняем местами два верхних элемента стека
                xchg();
                break;
            case '$': // Очищаем стек
                clear();
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

/* getop: получает следующий оператор или операнд */
int getop(char s[])
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
            // Если это оператор типа sin, exp или pow
            s[i++] = c;
            if (isalpha(c)) {
                while (isalpha(s[i++] = c = getch()))
                    ;
                s[--i] = '\0';
                if (strequ(s, "sin", 3) || strequ(s, "exp", 3) || strequ(s, "pow", 3) || strequ(s, "ungets", 6)){
                    ungetch(c);
                    return OPERAT;
                }
            }

            // Если это новая переменная
            int varname = tolower(s[i - 1]);
            if (c == '=') {

                i = 0;
                c = getch();

                /* накапливаем целую часть */
                if (isdigit(c)) {
                    s[i++] = c;
                    while (isdigit(s[i++] = c = getch())) ;
                }

                /* накапливаем дробную часть */
                if (c == '.') {
                    s[i++] = c;
                    while (isdigit(s[i++] = c = getch())) ;
                }
                // обрезаем строку
                if (!isdigit(s[i - 1]))
                    s[--i] = '\0';

                // создаём новую переменную
                var['z' - varname].value = atof(s);
                var['z' - varname].name = varname;
                var['z' - varname].isInit = true;
                lastVar = var['z' - varname];
                return VARIABLE;
            }

            // Это не число, но может быть переменная?
            if (c == ' ') {

                for (int j = 0; j < CALPHABET; j++) {
                    if (var[j].isInit && var[j].name == varname) {
                        // Внезапно попали на переменную, давайте занесём её в буфер
                        sprintf(s, "%f", var[j].value);
                        return NUMBER;
                    }
                }
            }
            if (c == EOF)
                return EOF;
            return s[0]; /* не число и не переменная */
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

/* push: положить значение f в стек */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf( "ошибка: стек полон, %g не помещается\n", f);
}

/* pop: взять с вершины стека и выдать в качестве результата */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf( "ошибка: стек пуст\n");
        return 0.0;
    }
}

/* Печатаем верхний элемент стека */
double top (void)
{
    if (sp > 0)
        return val[sp - 1];
    else {
        printf( "ошибка: стек пуст\n");
        return 0.0;
    }
}

/* Дублируем верхний элемент стека */
void clonetop (void)
{
    if (sp == MAXVAL) {
        printf( "ошибка: стек полон\n");
        return;
    }

    if (sp == 0) {
        printf( "ошибка: стек пуст\n");
        return;
    }
    double temp = val[sp - 1];
    val[sp++] = temp;
}

/* Меняем местами два верхних элемента стека */
void xchg (void) {

    if (sp > 1) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf( "ошибка: в стеке нет хотя бы двух элементов\n");
        return;
    }
}

/* Очищаем стек */
void clear (void) {
    sp = 0;
}

int getch(void) /* взять (возможно возвращенный) символ */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* вернуть символ на ввод */
{
    if (bufp >= BUFSIZE)
        printf ("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}
