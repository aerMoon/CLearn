#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "./../app.h"

int main(void) {

    setlocale(LC_ALL, "Rus");

    while (gettoken() != EOF) { /* 1-� ������� � ������ */
        strcpy(datatype, token); /* ��� ��� ������ */
    out[0] = '\0';
    dcl(); // ������ ��������� ����� ������
    if (tokentype != '\n' )
        printf ( "�������������� ������\n" ) ;
        printf("%s; %s %s\n", name, out, datatype);
    }
    return 0;
}
