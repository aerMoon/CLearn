/*
 * Упражнение 5.7. Напишите новую версию readlines, которая запоминала бы строки в массиве, определенном в main,
 * а не запрашивала память посредством программы alloc. Насколько быстрее эта программа?
 *
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* максимальное число строк */
#define ALLOCSIZE 10000 /* размер доступного пространства */

char *lineptr[MAXLINES]; /* указатели на строки */
int readlines(char *lineptr[], int nlines, char *linestore);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* сортировка строк */
int main(void)
{

    char allocbuf[ALLOCSIZE]; /* массив для хранения строк */
    int nlines; /* количество прочитанных строк */


    if ((nlines = readlines(lineptr, MAXLINES, allocbuf)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("ошибка: слишком много строк\n");
        return 1;
    }
}

#define MAXLEN 1000 /* максимальная длина строки */
int getline(char *, int);
char *alloc(int);

int getLine(char outBuf[], int maxLen) {

    // Получает строку из стандартного потока ввода

    int ch, pos = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n')
            break;
        outBuf[pos++] = ch;
        if (pos > maxLen) {
            --pos;
            break;
        }
    }
    outBuf[pos++] = 0;
    return pos;
}


/* readlines: чтение строк */
int readlines(char *lineptr[], int maxlines, char *linestore)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    p = linestore + strlen(linestore);
    while ((len = getLine(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (len + strlen(linestore)) >= ALLOCSIZE)
            return -1;
        else {
            line[len-1] = '\0'; /* убираем символ \n */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

/* writelines: печать строк */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}
