/*
 * Упражнение 5.5. Напишите варианты библиотечных функций strncpy, strncat и strncmp, которые оперируют с первыми
 * символами своих аргументов, число которых не превышает n. Например, strncpy(t, s, n) копирует не более n символов
 * t в s. Полные описания этих функций содержатся в приложении В.
 *
 * + Решил не делать релокацию памяти s, пусть вызывающий за ней следит.
 *
 */

#include <stdlib.h>
#include <stdio.h>

char *strncpy_my(char *s, char *ct, int n)
/*
 * копирует не более n символов строки ct в s; возвращает s. Дополняет результат символами '\0',
 * если символов в ct меньше n
 *
 */
{
    char *ptr = s;
    while (n--)
        *s++ = *ct++;
    if (*(ct - 1))
        *s = '\0';
    return ptr;
}

char *strncat_my(char *s, char *ct, int n)
/*
 * приписывает не более n символов ct к s, завершая s символом '\0'; возвращает s
 *
 */
{
    char *ptr = s;
    while (*s++)
        ;
    --s;
    while (n--)
        *s++ = *ct++;
    *s = '\0';
    return ptr;
}

char strncmp_my(char *cs, char *ct, int n)
/*
 * сравнивает не более n символов cs и ct; возвращает <0, если cs < ct, 0, если cs == ct, и >0, если cs > ct
 *
 */
{
    int i;
    for (i = 0; cs[i] == ct[i] && n--; i++)
        if (cs[i] == '\0')
            return 0;
    return cs[i] - ct[i];
}


int main(void) {
    char *buf = malloc(BUFSIZ);

    printf("Копируем в буфер слово:\t");
    printf(strncpy_my(buf, "Hello ", 6));

    printf("\nСоединяем две строки: \t");
    printf(strncat_my(buf, "World!", 6));

    printf("\nСравнение строк:\t\t%d\n", strncmp_my("string2", "string1", 6));

    free(buf);
    return 0;
}
