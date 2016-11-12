/*
 * Упражнение 5.14. Модифицируйте программу сортировки, чтобы она реагировала на параметр -r, указывающий,
 * что объекты нужно сортировать в обратном порядке, т. е. в порядке убывания. Обеспечьте, чтобы -r работал
 * и вместе с -n.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* максимальное число строк */

char *lineptr[MAXLINES]; /* указатели на строки */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void iqsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int inumcmp(char *, char *);
int istrcmp(char *, char *);

/* сортировка строк */
int main(int argc, char *argv[])
{
    int nlines; /* количество прочитанных строк */
    int numeric = 0; /* 1, если сорт, по числ. знач. */
    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        iqsort((void **) lineptr, 0, nlines-1, (int (*)(void*, void*))(numeric ? inumcmp : istrcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Введено слишком много строк\n");
        return 1;
    }
}

#define MAXLEN 1000 /* максимальная длина строки */

int igetline(char *, int);

/* readlines: чтение строк */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];nlines = 0;
    while ((len = igetline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = (char*)malloc(sizeof(char) * len)) == NULL)
        return -1;
    else {
        line[len-1] = '\0'; /* убираем символ \n */
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

/* writelines: печать строк */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf( "%s\n", *lineptr++);
}

/* iqsort: сортирует v[left]...v[right] по возрастанию */
void iqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {

    int i, last;
    void swap(void *v[], int, int);
    if (left >= right) /* ничего не делается, если */
        return; /* в массиве менее двух элементов */
    swap(v, left, (left + right )/2);last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
             swap(v, ++last, i);
    swap(v, left, last);
    iqsort(v, left, last-1, comp);
    iqsort(v, last+1, right, comp);
}

/* numcmp: сравнивает s1 и s2 как числа */
int inumcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* numcmp: сравнивает s1 и s2 как символы */
int istrcmp(char *s1, char *s2)
{
    if (*s1 < *s2)
        return -1;
    else if (*s1 > *s2)
        return 1;
    else
        return 0;
}


/* swap: поменять местами v[i] и v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int igetline(char *text, int maxlen) {
// Чтение строки из стандартного потока ввода

    int ch, pos = 0;
    while ((ch = getchar()) != EOF && pos < maxlen) {
        if (ch == '\n') {
            break;
        }
        text[pos] = ch;
        ++pos;
    }
    text[pos] = 0;
    if (ch == EOF)
        return EOF;
    return --pos;
}
