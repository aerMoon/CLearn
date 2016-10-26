/*
 * Упражнение 1.23. Напишите программу, убирающую все комментарии из любой Си-программы. Не забудьте
 * должным образом обработать строки символов и строковые константы. Комментарии в Си не могут быть
 * вложены друг в друга.
 *
 */

#include <stdio.h>

// Из условия видно, что надо убирать "//" и открывающий коммент "/*" и закрывающий "*/"
// Так же надо понимать находимся ли мы в строке или нет

#define INSTR 1
#define NOSTR 0

#define INCMNT 1
#define NOCMNT 1

#define STR_LEN 1024

int gettext(int buf[]);

int main(void) {

    int len;
    int string[STR_LEN];

    while ((len = gettext(string)) != EOF) {
        int status = NOSTR;
        int cmnt = NOCMNT;

        for (int i = 0; i < len; i++ ) {

            if ((string[i] == '"' || string[i] == '\'') && status == NOSTR && cmnt == NOCMNT) {
                // Начало строки
                status = INSTR;
            } else if ((string[i] == '"' || string[i] == '\'') && status == INSTR && cmnt == NOCMNT) {
                // Конец строки
                status = NOSTR;
            }

            if (string[i] == '/' && string[i + 1] == '/' && status == NOSTR && cmnt == NOCMNT) {
                // Обычный комментарий
                ++i;
                continue;
            } else if (string[i] == '/' && string[i + 1] == '*' && status == NOSTR) {
                // Начало длинного комментария
                cmnt = INCMNT;
                ++i;
                continue;
            } else if (string[i] == '*' && string[i + 1] == '/' && status == NOSTR) {
                // Конец длинного комментария
                cmnt = NOCMNT;
                ++i;
                continue;
            } else {
                // Просто символ
                putchar(string[i]);
            }
        }
    }

    return 0;
}

int gettext(int buf[]) {

    int pos = 0;
    int ch = getchar();
    while (ch != EOF && pos < STR_LEN) {
        buf[pos] = ch;
        ++pos;
        ch = getchar();
    }
    return pos;
}
