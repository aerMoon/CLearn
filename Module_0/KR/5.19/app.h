#ifndef APP_H
#define APP_H

#define MAXTOKEN 100
enum {NAME, PARENS, BRACKETS };
void dcl(void);
void dlrdcl(void);
int tokentype; /* тип последней лексемы */
char token[MAXTOKEN]; /* текст последней лексемы */
char name[MAXTOKEN]; /* имя */
char datatype[MAXTOKEN]; /* тип = char, int и т.д. */
char out[1000]; /* выдаваемый текст */

char buf [BUFSIZ];
int bufp = 0;

int getter(void)
{
    int c, getch(void);
    while ((c = getch()) == ' ' || c == '\t');
    return c;
}

int gettoken(void) /* возвращает следующую лексему */
{
    int c;
    void ungetch(int);
    char *p = token;
    while ((c = getter()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getter()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getter()) != ']'; )
            ;
        *p = '\0' ;
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getter());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

/* dcl: разбор объявителя */
void dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*'; ) /* подсчет звездочек */
        ns++;
    dlrdcl();
    while (ns-- > 0)
        strcat(out, " указ. на");
}

/* dirdcl: разбор собственно объявителя */
void dlrdcl(void)
{
    int type;
    if (tokentype == '(') { /* ( dcl ) */
        dcl();
        if (tokentype != ')')
            printf( "ошибка: пропущена )\n");
    } else if (tokentype == NAME) /* имя переменной */
        strcpy(name, token);
    else {
        printf("ошибка: должно быть name или (dcl)\n");
        exit(-1);
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " функц. возвр.");
        else {
            strcat(out, " массив");
            strcat(out, token);
            strcat(out, " из");
        }
}

int getch(void) /* взять (возможно возвращенный) символ */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* вернуть символ на ввод */
{
    if (bufp >= BUFSIZ)
        printf ("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}

#endif // APP_H

