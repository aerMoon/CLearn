/*
 * Упражнение 2.5. Напишите функцию any(s1, s2), которая возвращает либо ту позицию в s1, где стоит первый символ,
 * совпавший с любым из символов в s2, либо -1 (если ни один символ из s1 не совпадает с символами из s2).
 * (Стандартная библиотечная функция strpbrk делает то же самое, но выдает не номер позиции символа, а указатель
 * на символ.)
 *
 */

#include <stdio.h>

int any(char s1[], char s2[]);

int main(void) {

    char s1[] = "A typical font may contain hundreds or even thousands of glyphs";
    char s2[] = "Hello!!!";
    int pos = any(s1, s2);
    printf("Позиция первого найденного знака: %d\n", pos);
    return 0;
}

int any(char s1[], char s2[]) {

    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j])
                return i;
        }
    }
    return -1;
}
