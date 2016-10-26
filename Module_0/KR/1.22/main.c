/*
 * Упражнение 1.22. Напишите программу, печатающую символы входного потока так,
 * чтобы строки текста не выходили правее n-й позиции. Это значит, что каждая
 * строка, длина которой превышает n, должна печататься с переносом на следующие
 * строки. Место переноса следует "искать" после последнего символа, отличного
 * от символа-разделителя, расположенного левее n-й позиции. Позаботьтесь о том,
 * чтобы ваша программа вела себя разумно в случае очень длинных строк, а также
 * когда до n-й позиции не встречается ни одного символа пробела или табуляции.
 *
 */

#include <stdio.h>

#define MAX_LINE 80
#define BUF_SIZE 1024

int getline(int text[], int maxlen);
void wordwrap(int text[], int textlen, int startline, int limit);

int main(void) {

    int text[BUF_SIZE];
    int textlen;

    while ((textlen = getline(text, BUF_SIZE)) != 0) {

        wordwrap(text, textlen, 0, MAX_LINE);
        putchar('\n');
    }
    return 0;
}

int getline(int text[], int maxlen) {

    int ch, pos = 0;
    while ((ch = getchar()) != EOF && pos < maxlen) {
        if (ch == '\n') {
            break;
        }
        text[pos] = ch;
        ++pos;
    }
    return --pos;
}

void wordwrap(int text[], int textlen, int startline, int limit) {

    // 1. Массив символов для разбивания на строки
    // 2. Длина массива
    // 3. Символ с которого начинаем разбивать
    // 4. Ограничение строки


    if (startline + limit > textlen) {
        // Вывести огрызок и
        for (int i = startline; i <= textlen; i++) {
            putchar(text[i]);
        }
        return;
    }

    // Поиск удобного места для разбивки текста
    int wordpos = -1;
    for (int i = startline + limit; i >= startline; i--) {
        if (text[i] == ' ' || text[i] == '\t') {
            wordpos = i + 1; // Что бы убить пробел
            break;
        }
    }

    // Заботимся о особо длинных строках
    if (wordpos == -1) {
        wordpos = startline + limit;
    }

    // Печатаем строку до переноса
    for (int i = startline; i < wordpos; i++) {
        putchar(text[i]);
    }
    putchar('\n');

    // Рекурсия
    return wordwrap(text, textlen, wordpos, limit);

}

