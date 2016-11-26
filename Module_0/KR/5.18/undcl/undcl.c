#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "./../app.h"

int main(void) {

    int type;
    char temp[MAXTOKEN];
    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                sprintf(temp, "(*%s)", out);
        strcpy(out, temp);
    } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
    } else
        printf ("неверный элемент %s в фразе\n", token);
        printf("%s\n", out);
    }
}
