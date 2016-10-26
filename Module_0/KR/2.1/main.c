/*
 * Упражнение 2.1. Напишите программу, которая будет выдавать диапазоны значений типов char, short,
 * int и long, описанных как signed и как unsigned, с помощью печати соответствующих значений из
 * стандартных заголовочных файлов и путем прямого вычисления. Определите диапазоны чисел с плавающей
 * точкой различных типов. Вычислить эти диапазоны сложнее.
 *
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

double maxValueU(int bytes);
double maxValue(int bytes);
double minValue(int bytes);

int main(void) {

    // Чары
    printf("CHAR_MIN: %d\n", CHAR_MIN);
    printf("CHAR_MAX: %d\n", CHAR_MAX);
    printf("UCHAR_MAX: %d\n", UCHAR_MAX);
    // Шорты
    printf("SHRT_MIN: %d\n", SHRT_MIN);
    printf("SHRT_MAX: %d\n", SHRT_MAX);
    printf("USHRT_MAX: %d\n", USHRT_MAX);
    // Инты
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("UINT_MAX: %u\n", UINT_MAX);
    // Лонги
    printf("LONG_MIN: %ld\n", LONG_MIN);
    printf("LONG_MAX: %ld\n", LONG_MAX);
    printf("ULONG_MAX: %ul\n\n", ULONG_MAX);

    // Чары
    printf("CHAR_MIN: %g\n", minValue(sizeof(char)));
    printf("CHAR_MAX: %g\n", maxValue(sizeof(char)));
    printf("UCHAR_MAX: %g\n", maxValueU(sizeof(char)));
    // Шорты
    printf("SHRT_MIN: %g\n", minValue(sizeof(short)));
    printf("SHRT_MAX: %g\n", maxValue(sizeof(short)));
    printf("USHRT_MAX: %g\n", maxValueU(sizeof(short)));
    // Инты
    printf("INT_MIN: %0.lf\n", minValue(sizeof(int)));
    printf("INT_MAX: %0.lf\n", maxValue(sizeof(int)));
    printf("UINT_MAX: %ul\n", maxValueU(sizeof(int)));
    // Лонги
    printf("LONG_MIN: %0.lf\n", minValue(sizeof(long)));
    printf("LONG_MAX: %0.lf\n", maxValue(sizeof(long)));
    printf("ULONG_MAX: %ul\n\n", maxValueU(sizeof(long)));

    return 0;
}

double maxValueU(int bytes) {
    return pow(2, bytes * 8) - 1;
}

double maxValue(int bytes) {
    return pow(2, bytes * 8) / 2 - 1;
}

double minValue(int bytes) {
    return pow(2, bytes * 8) / -2;
}
