/*
 * Упражнение 4.10. В основу программы калькулятора можно положить применение функции getline, которая читает целиком
 * строку; при этом отпадает необходимость в getch и ungetch. Напишите программу, реализующую этот подход.
 *
 * p.s. Выпилил для наглядности getch и ungetch и заодно ungets потому что она была зависима от них.
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
#define UNKNOWN '3' /* признак неизвестности */
#define MAXVAL 100 /* максимальная глубина стека */
#define CALPHABET 26 /* Рарзмер алфавита */

struct rectVar{
    char name;
    double value;
    char isInit;
};

char buf[BUFSIZ]; /* буфер для ungetch */
int bufp = 0; /* след, свободная позиция в буфере */
int sp = 0; /* следующая свободная позиция в стеке */
double val[ MAXVAL ]; /* стек */
struct rectVar var[ CALPHABET ]; /* переменные */
struct rectVar lastVar; /* последняя добавленная переменная */

int getop (char []);
void push (double);
double pop (void);
double top (void);
void clonetop (void);
void xchg (void);
void clear (void);
int strequ(char s1[], char s2[], int len);

void calculate(int type, char s[]);
int getline(int text[], int maxlen);

/* калькулятор с обратной польской записью */
int main(void)
{
    char s[MAXOP];
    for (int i = 0; i < CALPHABET; i++)
        var[i].isInit = false;

    // Читаем строку целиком
    while (getop(s) != EOF)
        ;
    printf("получен EOF\n");
    return 0;
}

void calculate(int type, char s[]) {

    double op1, op2;
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

// Сравнить строки, 0 не равны, 1 равны
int strequ(char s1[], char s2[], int len) {

    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

// Чтение данных из стандартного потока ввода
int getline(int text[], int maxlen) {

    int ch, pos = 0;
    while ((ch = getchar()) != EOF && pos < maxlen) {
        text[pos] = ch;
        ++pos;
        if (ch == '\n')
            break;
    }
    return --pos;
}

/* getop: получает следующий оператор или операнд */
int getop(char s[])
{
    // Читаем строку целиком
    int pos = -1;
    int text[BUFSIZ];
    int len;
    if ((len = getline(text, BUFSIZ)) == EOF)
        return EOF;

next:
    ++pos;
    int spos = 0;

    // Пропускаем пустые символы в начале
    while ((text[pos] == ' ' || text[pos] == '\t') && pos < len)
        ++pos;

    // Проверяем на команды
    if (!isdigit(text[pos]) && text[pos] != '.') {
        if (text[pos] == '-') {
            // Проверка на операцию или знак числа
            if (!isdigit(text[++pos])) {
                calculate(text[--pos], s);
                goto next;
            }
        } else {
            // Если это оператор типа sin, exp или pow
            if (isalpha(text[pos])) {
                s[spos++] = text[pos++];
                while (isalpha(text[pos]))
                    s[spos++] = text[pos++];
                --pos;
                s[spos] = '\0';
                if (strequ(s, "sin", 3) || strequ(s, "exp", 3) || strequ(s, "pow", 3) || strequ(s, "ungets", 6)){
                    calculate(OPERAT, s);
                    goto next;
                }
            }

            // Если это новая переменная
            int varname = tolower(text[pos]);
            if (text[pos] == '=') {

                spos = 0;
                ++pos;

                /* накапливаем целую часть */
                while (isdigit(text[pos])) {
                    s[spos++] = text[pos++];
                }

                /* накапливаем дробную часть */
                if (text[pos] == '.') {
                    s[spos++] = text[pos];
                    while (isdigit(text[pos])) {
                        s[spos++] = text[pos++];
                    }
                }
                // обрезаем строку
                text[pos] = '\0';

                // создаём новую переменную
                var['z' - varname].value = atof(s);
                var['z' - varname].name = varname;
                var['z' - varname].isInit = true;
                lastVar = var['z' - varname];
                calculate(VARIABLE, s);
                goto next;
            }

            // Это не число, но может быть переменная?
            if (text[pos] == ' ') {

                for (int j = 0; j < CALPHABET; j++) {
                    if (var[j].isInit && var[j].name == varname) {
                        // Внезапно попали на переменную, давайте занесём её в буфер
                        sprintf(s, "%f", var[j].value);
                        calculate(NUMBER, s);
                        goto next;
                    }
                }
            }
            // Конец строки
            if (text[pos] == '\n') {
                calculate(text[pos], s);
                return text[pos];
            }
            // Конец ввода
            if (text[pos] == EOF)
                return text[pos];

            /* не число и не переменная */
            calculate(text[pos], s);
            goto next;
        }
    }

    /* накапливаем целую часть */
    while (isdigit(text[pos])) {
        s[spos++] = text[pos++];
    }
    /* накапливаем дробную часть */
    if (text[pos] == '.') {
        s[spos++] = text[pos];
        while (isdigit(text[pos])) {
            s[spos++] = text[pos++];
        }
    }
    // обрезаем строку
    s[spos] = '\0';
    calculate(NUMBER, s);
    goto next;
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
