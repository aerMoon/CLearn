/*
 * Упражнение 5.13. Напишите программу tail, печатающую n последних введенных строк. По умолчанию значение n равно 10,
 * но при желании n можно задать с помощью аргумента. Обращение вида
 *
 *      tail -n
 *
 * печатает n последних строк. Программа должна вести себя осмысленно при любых входных данных и любом значении n.
 * Напишите программу так, чтобы наилучшим образом использовать память; запоминание строк организуйте, как в программе
 * сортировки, описанной в параграфе 5.6, а не на основе двумерного массива с фиксированным размером строки.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

int getline(char *text, int maxlen) {
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

int main(int argc, char *argv[]) {

    // Получаем N
    int count = 10;
    if (argc == 3 && strcmp(argv[1], "-n") == 0)  {
        count = atoi(argv[2]);
    } else {
        printf("Error in argument vector\nuse: tail -n #NUM\n");
    }

    // Выделяем память для строк
    char *buf = (char*)malloc(BUFSIZ);
    TStrStack stack;
    InitStrStack(&stack);
    stack.init(count);

    // Читаем строки из стандартного ввода
    while (getline(buf, BUFSIZ) != EOF) {
        stack.push(buf);
    }

    // Выводим N строк
    for (int i = 0; i < stack.count(); i++) {
        stack.take(i, buf);
        if (buf[0] == '\0')
            continue;
        printf("%d => %s\n", i + 1, buf);
    }

    // Смываем за собой
    free(buf);
    stack.free();
    return 0;
}
