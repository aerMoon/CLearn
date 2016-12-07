/*
 * Упражнение 6.2. Напишите программу, которая читает текст Си-программы и печатает в алфавитном порядке все группы
 * имен переменных, в которых совпадают первые 6 символов, но последующие в чем-то различаются. Не обрабатывайте
 * внутренности закавыченных строк и комментариев. Число 6 сделайте параметром, задаваемым в командной строке.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode { /* узел дерева */
    char *word; /* указатель на текст */
    int count; /* число вхождений */
    struct tnode *left; /* левый сын */
    struct tnode *right; /* правый сын */
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *, int level);
int getword(char *, int);
struct tnode *talloc(void);


int main(int argc, char *argv[]) {

    int num;

    if (argc == 2)
        num = atoi(argv[1]);
    else if (argc < 2)
        num = 6;
    else {
        printf("usage: tree <number>\n");
        exit(-1);
    }

    struct tnode *root;
    root = NULL;

    char word[MAXWORD];
    while(getword(word, MAXWORD) != EOF)
        // Уберём слова в которых меньше Num символов
        if (isalpha(word[0]) && (strlen((const char *)&word[0]) >= num))
            root = addtree(root, word, num);

    treeprint(root, num);
    return 0;
}

/* addtree: добавляет узел со словом w в р или ниже него */
struct tnode *addtree(struct tnode *p, char *w, int level)
{
    int cond;
    if (p == NULL) { /* слово встречается впервые */
        p = talloc(); /* создается новый узел */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, level)) == 0)
        p->count++; /* это слово уже встречалось */
    else if (cond < 0) /* меньше корня левого поддерева */
        p->left = addtree(p->left, w, level);
    else /* больше корня правого поддерева */
        p->right = addtree(p->right, w, level);
    return p;
}

/* treeprint: упорядоченная печать дерева р */
void treeprint(struct tnode *p, int level)
{
    if (p != NULL) {
        treeprint(p->left, level);
        printf("%4d ", p->count);
        for (int i = 0; i < level; i++)
            putchar(p->word[i]);
        printf("[*]\n");
        treeprint(p->right, level);
    }
}

/* talloc: создает tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* getword: принимает следующее слово или символ из ввода */
int getword (char *word, int lim) {

    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()));
        if (c == '"') {
            // Пропускаем строки
            while ((c = getch()) != '"' && c != EOF)
                ;
        } else if (c == '/') {
            // Комментарий
            if ((c = getch()) == '/')
                while ((c = getch()) != 10 && c != EOF)
                    ;
        } else if (c != EOF) {
            *w++ = c;
        }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

char buf [BUFSIZ];
int bufp = 0;

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


