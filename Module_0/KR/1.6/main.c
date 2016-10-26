/*
 * Упражнение 1.6. Убедитесь в том, что выражение getchar() != EOF получает значение 0 или 1 .
 */

#include <stdio.h>

void main() {

    printf("Введите q для выхода\n");
    int c = getchar();
    while (c != 'q') {
        printf("getchar() != EOF получает значение: %d\n", (c != EOF));
        c = getchar();
    }
    printf("Выходим\n");
}
