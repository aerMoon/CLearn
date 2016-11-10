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

int main(int argc, char *argv[]) {

    // Получаем N
    int count = 10;
    if (argc == 3 && strcmp(argv[1], "-n") == 0)  {
        count = atoi(argv[2]);
    } else {
        printf("Error in argument vector\nuse: tail -n #NUM\n");
    }

    // Читаем строки из стандартного ввода

    // Выводим N строк


    return 0;
}
