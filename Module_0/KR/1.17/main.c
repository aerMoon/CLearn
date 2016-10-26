/*
 * Упражнение 1.17. Напишите программу печати всех вводимых строк, содержащих более 80 символов.
 *
 */

#include <stdio.h>

int main(void) {

#define MAX_LINE 80

    int line[MAX_LINE];

    for (int i = 0; i < MAX_LINE; i++) {
        line[i] = EOF;
    }

    int ch, position = 0;
    while ((ch = getchar()) != EOF) {

        if (ch == '\n') {
            // Начинаем новую строку
            position = 0;
            for (int i = 0; i < MAX_LINE; i++) {
                line[i] = EOF;
            }
            continue;
        }

        if (position == MAX_LINE)
        {
            // Буфер из 80-и символов заполнен, выводим его
            for (int i = 0; i < MAX_LINE; i++) {
                if (line[i] != EOF)
                    putchar(line[i]);
                line[i] = EOF;
            }
            // Печатаем новый символ
            putchar(ch);
        } else if (position > MAX_LINE) {
            // Печатаем каждый символ, если строка больше 80-и знаков
            putchar(ch);
        } else {
            // Заполняем буфер новым символом
            if (position < MAX_LINE)
                line[position] = ch;
            ++position;
        }
    }


    return 0;
}
