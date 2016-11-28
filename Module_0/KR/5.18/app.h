#ifndef APP_H
#define APP_H

#define MAXTOKEN 100
enum {NAME, PARENS, BRACKETS };
void dcl(void);
void dlrdcl(void);
int tokentype; /* ��� ��������� ������� */
char token[MAXTOKEN]; /* ����� ��������� ������� */
char name[MAXTOKEN]; /* ��� */
char datatype[MAXTOKEN]; /* ��� = char, int � �.�. */
char out[1000]; /* ���������� ����� */

char buf [BUFSIZ];
int bufp = 0;

int getter(void)
{
    int c, getch(void);
    while ((c = getch()) == ' ' || c == '\t');
    return c;
}

int gettoken(void) /* ���������� ��������� ������� */
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

/* dcl: ������ ���������� */
void dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*'; ) /* ������� ��������� */
        ns++;
    dlrdcl();
    while (ns-- > 0)
        strcat(out, " ����. ��");
}

/* dirdcl: ������ ���������� ���������� */
void dlrdcl(void)
{
    int type;
    if (tokentype == '(') { /* ( dcl ) */
        dcl();
        if (tokentype != ')')
            printf( "������: ��������� )\n");
    } else if (tokentype == NAME) /* ��� ���������� */
        strcpy(name, token);
    else {
        printf("������: ������ ���� name ��� (dcl)\n");
        exit(-1);
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " �����. �����.");
        else {
            strcat(out, " ������");
            strcat(out, token);
            strcat(out, " ��");
        }
}

int getch(void) /* ����� (�������� ������������) ������ */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* ������� ������ �� ���� */
{
    if (bufp >= BUFSIZ)
        printf ("ungetch: ������� ����� ��������\n");
    else
        buf[bufp++] = c;
}

#endif // APP_H

