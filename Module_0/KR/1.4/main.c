/*
 * Упражнение  1.4. Напишите программу, которая будет печатать таблицу соответствия температур по Цельсию температурам
 * по Фаренгейту
 *
 */

#include<stdio.h>
/* печать таблицы температур по Фаренгейту и Цельсию для fahr = 0, 20 ... 300; вариант с плавающей точкой */


void main() {
    float fahr, celsius;
    int lower,  upper, step;

    lower = 0; /* нижняя граница таблицы температур */
    upper = 300; /* верхняя граница */
    step = 20; /* шаг */
    celsius = lower;

    printf_s("-------------\n| C  |   F  |\n-------------\n");
    while (celsius <= upper) {
        fahr = (9.0 / 5.0) * celsius + 32.0;
        printf_s("|%3.0f |%6.1f|\n", celsius, fahr);
        celsius = celsius + step;
    }
    printf_s("-------------\n");
}
