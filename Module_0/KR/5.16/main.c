/*
 * Упражнение 5.16. Предусмотрите в программе необязательный параметр -d, который заставит программу при сравнении
 * учитывать только буквы, цифры и пробелы. Организуйте программу таким образом, чтобы этот параметр мог работать
 * вместе с параметром -f.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000 /* максимальное число строк */
int reverse = 0;
int insensitive = 0;
int paramd = 0;
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
    extern int reverse;
    extern int insensitive;
    for (int i = 0; i < argc; i++) {
        if (argc > 1 && strcmp(argv[i], "-n") == 0) {
            numeric = 1;
        } else if (argc > 1 && strcmp(argv[i], "-r") == 0) {
            reverse = 1;
        } else if (argc > 1 && strcmp(argv[i], "-f") == 0) {
            insensitive = 1;
        } else if (argc > 1 && strcmp(argv[i], "-d") == 0) {
            paramd = 1;
        }
    }
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
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = igetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = (char*)malloc(sizeof(char) * len)) == NULL)
            return -1;
        else {
            // ++ Вот так и не осознал как же должна правильно работать igetline, что бы и тут не затирался символ и
            // выход по EOF работал бы
            // line[len-1] = '\0'; /* убираем символ \n */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: печать строк */
void writelines(char *lineptr[], int nlines)
{
    extern int reverse;
    if (reverse) {
        for (int i = 1; i <= nlines; i++)
            printf("%s\n", lineptr[nlines - i]);
    } else {
        while (nlines-- > 0)
            printf("%s\n", *lineptr++);
    }
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

/* numcmp: сравнивает s1 и s2 как строки */
int istrcmp(char *s1, char *s2)
{    
    if (paramd) {
        // Убираем лишние символы в первой строке
        int pos = 0;
        int pos1 = 0;
        while (s1[pos1] != '\0') {
            if (isalnum(s1[pos1]) || (s1[pos1] == ' '))
                s1[pos++] = s1[pos1];
            ++pos1;
        }
        s1[pos] = '\0';
        // Убираем лишние символы во второй строке
        pos = 0;
        pos1 = 0;
        while (s2[pos1] != '\0') {
            if (isalnum(s2[pos1]) || (s2[pos1] == ' '))
                s2[pos++] = s2[pos1];
            ++pos1;
        }
        s2[pos] = '\0';
    }
    if (insensitive) {
        return strcmpi(s1, s2);
    } else {
        return strcmp(s1, s2);
    }
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
        text[pos++] = ch;
    }
    text[pos++] = '\0';
    return --pos;
}
