/*
 * Упражнение 1.24. Напишите программу, проверяющую Си-программы на элементарные синтаксические
 * ошибки вроде несбалансированности скобок всех видов. Не забудьте о кавычках (одиночных и двойных),
 * эскейп-последовательностях (\...) и комментариях. (Это сложная программа, если писать ее для общего
 * случая.)
 *
 */

#include <stdio.h>

#define MAX_LEN 1024
#define false 0
#define true !false

// Вообще енумы не проходили ещё, но просто грех их не заюзать (=
enum CodeState {csAnyCode, csInChar,  csInString, csInCommentLine, csInCommentMultiLine, csEscape};

// Одинарные ковычки
int countOfQuotes = 0;
// Двойные ковычки
int countOfDQuotes = 0;
// Количество многостроковых коментариев
int countOfMultiLineComment = 0;
// Количество escape-последовательностей
int countOfEscapes = 0;
// Количество открывающих круглых скобок
int countOfRoundBracketOpened = 0;
// Количество закрывающих круглых скобок
int countOfRoundBracketClosed = 0;
// Количество открывающих фигурных скобок
int countOfCurtyBracketOpened = 0;
// Количество закрывающих фигурных скобок
int countOfCurtyBracketClosed = 0;
// Количество открывающих квадратных скобок
int countOfSquareBracketOpened = 0;
// Количество закрывающих квадратных скобок
int countOfSquareBracketClosed = 0;

int gettext(int text[]);
void analizer(int text[], int textlen);

int main(void) {

    extern int countOfQuotes;
    extern int countOfDQuotes;
    extern int countOfMultiLineComment;
    extern int countOfEscapes;
    extern int countOfRoundBracketOpened;
    extern int countOfRoundBracketClosed;
    extern int countOfCurtyBracketOpened;
    extern int countOfCurtyBracketClosed;
    extern int countOfSquareBracketOpened;
    extern int countOfSquareBracketClosed;

    int textlen;
    int text[MAX_LEN];

    while ((textlen = gettext(text)) != 0) {

        analizer(text, textlen);

        printf("Количество одинарных ковычек: \t %d\n", countOfQuotes);
        if (countOfQuotes % 2 > 0) {
            printf("\tОШИБКА: Не сбалансированное количество одинарных ковычек\n\n");
        }
        printf("Количество двойных ковычек: \t %d\n", countOfDQuotes);
        if (countOfQuotes % 2 > 0) {
            printf("\tОШИБКА: Не сбалансированное количество двойных ковычек\n\n");
        }
        printf("Количество многостроковых комментариев: \t %d\n", countOfMultiLineComment);
        if (countOfQuotes % 2 > 0) {
            printf("\tОШИБКА: Мультисроковый комментарий или комментарии не закрыты\n\n");
        }
        printf("Количество esc-последовательностей: \t %d\n", countOfEscapes);

        printf("Количество круглых открывающих скобок: \t %d\n", countOfRoundBracketOpened);
        printf("Количество круглых закрывающих скобок: \t %d\n", countOfRoundBracketClosed);
        if (countOfRoundBracketOpened != countOfRoundBracketClosed) {
            printf("\tОШИБКА: Не сбалансированное количество круглых скобок\n\n");
        }
        printf("Количество фигурных открывающих скобок: \t %d\n", countOfCurtyBracketOpened);
        printf("Количество фигурных закрывающих скобок: \t %d\n", countOfCurtyBracketClosed);
        if (countOfCurtyBracketOpened != countOfCurtyBracketClosed) {
            printf("\tОШИБКА: Не сбалансированное количество фигурных скобок\n\n");
        }
        printf("Количество квадратных открывающих скобок: \t %d\n", countOfSquareBracketOpened);
        printf("Количество квадратных закрывающих скобок: \t %d\n", countOfSquareBracketClosed);
        if (countOfSquareBracketOpened != countOfSquareBracketClosed) {
            printf("\tОШИБКА: Не сбалансированное количество квадратных скобок\n\n");
        }

    }
    return 0;
}

int gettext(int text[]) {

    int pos = 0;
    int ch = getchar();
    while (ch != EOF && pos < MAX_LEN) {
        text[pos] = ch;
        ++pos;
        ch = getchar();
    }
    return pos;
}

void analizer(int text[], int textlen) {

    extern int countOfQuotes;
    extern int countOfDQuotes;
    extern int countOfMultiLineComment;
    extern int countOfEscapes;
    extern int countOfRoundBracketOpened;
    extern int countOfRoundBracketClosed;
    extern int countOfCurtyBracketOpened;
    extern int countOfCurtyBracketClosed;
    extern int countOfSquareBracketOpened;
    extern int countOfSquareBracketClosed;

    countOfQuotes = 0;
    countOfDQuotes = 0;
    countOfMultiLineComment = 0;
    countOfEscapes = 0;
    countOfRoundBracketOpened = 0;
    countOfRoundBracketClosed = 0;
    countOfCurtyBracketOpened = 0;
    countOfCurtyBracketClosed = 0;
    countOfSquareBracketOpened = 0;
    countOfSquareBracketClosed = 0;

    int pos = 0;
    int find = false;
    int startOfBlock;
    enum CodeState oldstate, state = csAnyCode;
    int escapes[] = {'a', 'b', 'f', 'e', 'n', 'r', 't', 'v', '\'', '"', '\\', '?', 'x', 'o', '0', '\0'};

    for (int i = 0; i < textlen; i++ ) {

        switch ( state ) {

            case csInChar:
                // Если одинарная кавычка закрывает символ
                if (text[i] == '\'') {
                    state = csAnyCode;
                    ++countOfQuotes;
                    // Проверяем на ошибку написания символа
                    if (!((i == startOfBlock + 2) || (i == startOfBlock + 3 && text[startOfBlock + 1] == '\\'))) {
                        printf("Синтаксическая ошибка: char определён не верно - позиция от начала строки кода %d\n", startOfBlock);
                        continue;
                    }
                }
                // Проверяем на Escape последовательность
                if (text[i] == '\\')
                {
                    oldstate = state;
                    state = csEscape;
                }
                break;
            case csInString:
                // Если двойная кавычка закрывает строку
                if (text[i] == '"') {
                    state = csAnyCode;
                    ++countOfDQuotes;
                }
                // Проверяем на Escape последовательность
                if (text[i] == '\\')
                {
                    oldstate = state;
                    state = csEscape;
                }
                // Если строка не завершена
                if (text[i] == '\n') {
                    printf("Синтаксическая ошибка: строка не детерминирована - позиция от начала строки кода %d\n", startOfBlock);
                    state = csAnyCode;
                }
                break;
            case csInCommentLine:
                if (text[i] == '\n') {
                    state = csAnyCode;
                }
                break;
            case csInCommentMultiLine:
                if (text[i] == '*' && text[i] == '/') {
                    state = csAnyCode;
                }
                break;
            case csEscape:
                pos = 0;
                find = false;
                state = oldstate;
                // Ищем по списку допустимых символов esc-последовательности
                while (escapes[pos] != '\0') {
                    if (escapes[pos] == text[i]) {
                        // Правильная ESCAPE последовательность
                        find = true;
                        break;
                    }
                    ++pos;
                }
                // Если не нашли, то выводим ошибку
                if (find != true) {
                    printf("Синтаксическая ошибка: escape последовательность не верна - позиция от начала строки кода %d\n", startOfBlock);
                }
                ++countOfEscapes;
                break;
            default:
                // Если это открывающая круглая скобка
                if (text[i] == '(') {
                    ++countOfRoundBracketOpened;
                }
                // Если это закрывающая круглая скобка
                if (text[i] == ')') {
                    ++countOfRoundBracketClosed;
                }
                // Если это открывающая фигурная скобка
                if (text[i] == '{') {
                    ++countOfCurtyBracketOpened;
                }
                // Если это закрывающая фигурная скобка
                if (text[i] == '}') {
                    ++countOfCurtyBracketClosed;
                }
                // Если это открывающая квадратная скобка
                if (text[i] == '[') {
                    ++countOfSquareBracketOpened;
                }
                // Если это закрывающая квадратная скобка
                if (text[i] == ']') {
                    ++countOfSquareBracketClosed;
                }
                // Если это начало символа
                if (text[i] == '\'') {
                    state = csInChar;
                    startOfBlock = i;
                    ++countOfQuotes;
                }
                // Если это начало строки
                if (text[i] == '"') {
                    state = csInString;
                    startOfBlock = i;
                    ++countOfDQuotes;
                }
                // Если это начало коментария
                if (text[i] == '/') {
                    if (text[i + 1] == '/') {
                        state = csInCommentLine;
                        startOfBlock = i;
                    } else {
                        printf("Синтаксическая ошибка: коментарий не найден - позиция от начала строки кода %d\n", i);
                    }
                }
                // Если это начало многострочного коментария
                if (text[i] == '/' && text[i + 1] == '*' ) {
                    state = csInCommentMultiLine;
                    startOfBlock = i;
                    ++countOfMultiLineComment;
                }
        }
    }
}
