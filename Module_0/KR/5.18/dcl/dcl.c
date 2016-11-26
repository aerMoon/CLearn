#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "./../app.h"

int main(void) {

    while (gettoken() != EOF) { /* 1-я лексема в строке */
        strcpy(datatype, token); /* это тип данных */
    out[0] = '\0';
    dcl(); // разбор остальной части строки
    if (tokentype != '\n' )
        printf ( "синтаксическая ошибка\n" ) ;
        printf("%s; %s %s\n", name, out, datatype);
    }
    return 0;
}
