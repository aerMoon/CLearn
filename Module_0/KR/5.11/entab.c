/*
 * Упражнение 5.11. Усовершенствуйте программы entab и detab (см. упражнения 1.20 и 1.21) таким образом, чтобы через
 * аргументы можно было задавать список "стопов" табуляции.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARG_TABSTOP "-ts"

#define INSPACE 1
#define NOSPACE 0
#define MAX_LEN 1024

int getline(int outBuf[]);
void fill(int buf[], int ch, int len);
void output(int buf[], int len);

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
    int len;
    int inBuf[MAX_LEN];
    int outBuf[MAX_LEN];
    fill(inBuf, EOF, MAX_LEN);
    fill(outBuf, EOF, MAX_LEN);

    while ((len = getline(inBuf)) != 0) {

        int selstart, selend;
        int outSeek = 0;
        int status = NOSPACE;
        for (int inSeek = 0; inSeek < len; inSeek++) {

            if (inBuf[inSeek] == ' ') {
                // Нашли пробел
                if (status == NOSPACE) {
                    status = INSPACE;
                    selstart = inSeek;
                }

            } else {
                // Обычные символы тупо переносим
                if (status == INSPACE) {
                    selend = inSeek;
                    status = NOSPACE;

                    for (int i = selstart; i <= selend; i++) {

                        // Ищем сколько пробелов до стопа от i
                        int nextstop = tabstop * (i / tabstop) + tabstop;
                        // Если можем его забить до конца табом, то действуем
                        if (nextstop <= selend) {
                            outBuf[outSeek] = '\t';
                            ++outSeek;
                            i += tabstop;
                            continue;
                        }
                        // Если не влазием табом, просто вводим пробелы
                        outBuf[outSeek] = ' ';
                        ++outSeek;
                    }
                }
                outBuf[outSeek] = inBuf[inSeek];
                ++outSeek;
            }

        }

        output(outBuf, outSeek);
        fill(inBuf, EOF, MAX_LEN);
        fill(outBuf, EOF, MAX_LEN);
    }
    return 0;
}

void output(int buf[], int len) {

    for (int i = 0; i < len; i++) {
        // Табы и пробелы печатаем для отладки другими символами
#ifdef DEBUG
        if (buf[i] == '\t') {
            for (int j = 0; j < TABSTOP; j++)
                putchar('.');

        } else if (buf[i] == ' ') {
            putchar('-');
        } else {
#endif
            putchar(buf[i]);
#ifdef DEBUG
        }
#endif
    }
    putchar('\n');
}


int getline(int outBuf[]) {
    // Получить строку
    int ch, pos = 0;
    while ((ch = getchar()) != EOF) {
        if ((ch == '\n') || (pos > MAX_LEN))
            break;
        outBuf[pos] = ch;
        ++pos;
    }
    return pos;
}

void fill(int buf[], int ch, int len) {
    // Очистка буфера
    for (int i = 0; i < len; i++ ) {
        buf[i] = ch;
    }
}
