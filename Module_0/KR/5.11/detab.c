/*
 * Упражнение 5.11. Усовершенствуйте программы entab и detab (см. упражнения 1.20 и 1.21) таким образом, чтобы через
 * аргументы можно было задавать список "стопов" табуляции.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARG_TABSTOP "-ts"

int main(int argc, char *argv[]) {

    // Определим размер табстопа через аргумент
    int tabstop;
    if (argc == 3 && strcmp(argv[1], ARG_TABSTOP) == 0) {
        printf("I Use manual tabstop: %s\n", argv[2]);
        tabstop = atoi(argv[2]);
    } else {
        printf("Error in argument line. I Use standart tabstop: 8\n");
        tabstop = 8;
    }

    // Выполним преобразование
    int ch, pos = 0;
    while ((ch = getchar()) != EOF) {

        if (ch == '\t') {
            for (int i = pos; i < tabstop; i++) {
                putchar(' ');
            }
            pos = 0;
        } else if (ch == '\n') {
            pos = 0;
            putchar(ch);
        } else {
             ++pos;
             if (pos > tabstop) {
                pos = 0;
             }
             putchar(ch);
        }
    }
}
