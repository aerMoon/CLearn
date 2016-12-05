/*
 * Упражнение 6.1. Наша версия getword не обрабатывает должным образом знак подчеркивания, строковые константы,
 * комментарии и управляющие строки препроцессора. Напишите более совершенный вариант программы.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100

struct key {
    char *word;
    int count;
} keytab[] = { // GCC bug 53119
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"double", 0},
    {"int", 0},
    {"struct", 0},
    {"else", 0},
    {"long", 0},
    {"switch", 0},
    {"enum", 0},
    {"register", 0},
    {"typedef", 0},
    {"extern", 0},
    {"return", 0},
    {"union", 0},
    {"float", 0},
    {"short", 0},
    {"for", 0},
    {"signed", 0},
    {"goto", 0},
    {"sizeof", 0},
    {"do", 0},
    {"if", 0},
    {"static", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};


int getword(char *, int);
int binsearch(char *, struct key *, int);

#define NKEYS (sizeof keytab / sizeof keytab[0])

int main(void) {

    int n;
    char word[MAXWORD];
    while(getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* getword: принимает следующее слово или символ из ввода */
int getword (char *word, int lim) {

    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()));
        if (c == '"') {
            // Пропускаем строки
            while ((c = getch()) != '"' && c != EOF)
                ;
        } else if (c == '#') {
            // Препроцессор
            while ((c = getch()) != 10 && c != EOF)
                ;
        } else if (c == '/') {
            // Комментарий
            if ((c = getch()) == '/')
                while ((c = getch()) != 10 && c != EOF)
                    ;
        } else if (c != EOF) {
            *w++ = c;
        }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

/* binsearch: найти слово в tab[0] ... tab[n - Т] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1 ;
    while (low <= high) {
        mid = (low + high)/2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

char buf [BUFSIZ];
int bufp = 0;

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
