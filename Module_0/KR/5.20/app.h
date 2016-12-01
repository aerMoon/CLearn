#ifndef APP_H
#define APP_H

#define MAXTOKEN 100
enum {NAME, PARENS, BRACKETS };
int gettoken(void);
int nexttoken(void);
void dlrdcl(void);
void dcl(void);
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

enum {NO, YES};
int prevtoken = NO;

int nexttoken(void)
{
    int type;
    type = gettoken();
    prevtoken = YES;
    return type;
}

int getch(void);

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

/* dirdcl: разбор собственно объявителя */
void dlrdcl(void)
{
    int type;
    void params_dcl(void);

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("oшибкa: пропущена )\n");
            exit(-1);
        }
    } else if (tokentype == NAME) {
        if (name[0] == '\0')
            strcpy(name, token);
    }
    else {
        prevtoken = YES;
    }

    while((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, "функц. возвр.");
        else if (type == '(') {
            strcat(out, " функц. приним. ");
            params_dcl();
            strcat(out, " и возвр. ");
        } else {
            strcat(out, " массив ");
            strcat(out, token);
            strcat(out, " из ");
        }
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

void params_dcl(void)
{
    void type_dcl(void);

    do {
        type_dcl();
    } while (tokentype == ',');
    if (tokentype != ')') {
        printf("oшибкa: пропущена ) в объявлении параметров\n");
        prevtoken = YES;
    }
}

void type_dcl(void)
{
    char t[MAXTOKEN];
    int istypename(char []);
    int istypequal(char []);

    t[0] = '\0';
    gettoken();

    do {
        if (tokentype != NAME) {
            prevtoken = YES;
            dcl();
        } else if (istypename(token)) {
            strcat(t, token);
            gettoken();
        } else if (istypequal(token)) {
            strcat(t, token);
            gettoken();
        } else {
            printf("ошибка: неизвестный параметр %s\n", token);
            prevtoken = YES;
        }
    } while (tokentype == ',' && tokentype == ')');
    strcat(out, t);
    if (tokentype == ',')
        strcat(out, ", ");
}

int istypename(char name[])
{
    int i=0;
    char *types[] = {"char", "int", "float"};
    int ntypes = 3;

    while (ntypes--)
        if (strcmp(name, types[i++]) == 0)
            return 1;

    return 0;
}

int istypequal(char qual[])
{
    int i=0;
    char *quals[] = {"const", "volatile"};
    int nquals = 2;

    while (nquals--)
        if (strcmp(qual, quals[i++]) == 0)
            return 1;

    return 0;
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

