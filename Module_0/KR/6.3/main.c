/*
 * Упражнение 6.3. Напишите программу печати таблицы "перекрестных ссылок", которая будет печатать все слова документа
 * и указывать для каждого из них номера строк, где оно встретилось. Программа должна игнорировать "шумовые" слова,
 * такие как "и", "или" и пр.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXLINK 5

struct tnode {           /* узел дерева */
    char *word;           /* указатель на текст */
    int nline[MAXLINK];   /* массив номеров строк */
    int count;            /* индекс в nline[] */
    struct tnode *left;  /* левый дочерний узел */
    struct tnode *right; /* правый дочерний узел */
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int num;                  /* Максимальная длина "шумового" слова */
int lnum = 0;             /* Инициализация счетчика строк */

int main(int argc, char *argv[]) {

    struct tnode *root;
    char word[MAXWORD];

    if (argc == 2)
        num = atoi(argv[1]);
    else if (argc < 2)
        num = 2;
    else {
        printf("usage: linktree <number>\n");
        exit(-1);
    }

    root = NULL;
    while (getword (word, MAXWORD) != EOF)
        if (isalpha(word[0]) && strlen(word) > num)
            root = addtree(root, word);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *mystrdup(char *);

/* addtree: добавляет узел со словом w в р или ниже него */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {  /* слово встречается впервые */
        p = talloc(); /* создается новый узел */
        p->word = strdup(w);
        p->nline[p->count] = lnum;
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->nline[p->count++] = lnum; /* это слово уже встречалось */
    }
    else if (cond < 0)        /* меньше корня левого поддерева */
        p->left = addtree(p->left, w);
    else                      /* больше корня правого поддерева */
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: упорядоченная печать дерева р */
void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint (p->left);
        printf("\n%s ", p->word);
        for (i = 0; i < MAXLINK; i++)
            printf("%2d ",p->nline[i]);
        treeprint(p->right);
    }
}

/* talloc: создает tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* getword: принимает следующее слово или символ из ввода */
int getword (char *word, int lim)
{
    int c, t, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) && c != '\n');
    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_') {
        for ( ; --lim > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }
            else if (*w == '\n') {
                lnum++;
                ungetch(*w);
                break;
            }
        }
    }
    else if (c == '"') {
        while ((t = getch()) != c && t != EOF);
    }
    else if (c == '/') {
        if ((t = getch()) == '*') {
            while ((t = getch()) != EOF )
                if (t == '*') {
                    if ((t = getch()) == '/')
                        break;
                    else
                        ungetch(t);
                }
        }
            else
                ungetch(t);
    }
    else if (c == '\n')
        lnum++;
    *w = '\0';
    return c;
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


