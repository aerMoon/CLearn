/*
 * Упражнение 2.4. Напишите версию функции squeeze(s1, s2), которая удаляет из s1 все символы,
 * встречающиеся в строке s2.
 *
 */

#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(void) {

    char str1[] = "Hello world\n";
    char str2[] = "ol";
    squeeze(str1, str2);
    printf(str1);
    return 0;
}

/* squeeze: удаляет все с из s - в чём разница этих вариантов???
void squeeze(char s1[], char s2[])
{
    int i, j, pos;
    for (pos = i = 0; s1[i] != '\0'; i++) {
        s1[pos++] = s1[i];
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                pos--;
    }
    s1[i] = '\0';
}*/

void squeeze(char s1[], char s2[])
{
    int i, j, k;

    for (j = i = 0; s1[i] != '\0'; i++) {
        s1[j++] = s1[i];
        for (k = 0; s2[k] != '\0'; k++)
            if (s1[i] == s2[k])
                j--;
    }
    s1[j] = '\0';
}
