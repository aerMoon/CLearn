/*
 * Упражнение 6.6. Реализуйте простую версию #define-процессора (без аргументов), которая использовала бы программы
 * этого параграфа и годилась бы для Си-программ. Вам могут помочь программы getch и ungetch.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct nlist { /* элемент таблицы */
    struct nlist *next; /* указатель на следующий элемент */
    char *name; /* определенное имя */
    char *defn; /* замещающий текст */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* таблица указателей */

struct nlist *lookup(char *);
unsigned hash(char *s);
struct nlist *install(char *name, char *defn);
char undef(char *s);

int main(void) {

    // Надо заполнить таблицу и написать undef
    printf("Вставляем два элемента в таблицу\n");
    install("first", "test1");
    install("last", "test2");

    printf("\nНаходим элемент first в таблице\n");
    printf("%s\n", lookup("first")->defn);
    printf("Находим элемент last в таблице\n");
    printf("%s\n", lookup("last")->defn);

    printf("\nУдаляем элемент first в таблице\n");
    undef("first");

    printf("\nНаходим элемент first в таблице\n");
    printf("%s\n", lookup("first")->defn);
    return 0;
}

/* install: заносит имя и текст (name, defn) в таблицу */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* не найден */
        np = (struct nlist *) malloc(sizeof(*np));
    if ((np == NULL) || ((np->name = strdup(name)) == NULL))
        return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
    } else /* уже имеется */
        free((void *) np->defn); /* освобождаем прежний defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* hash: получает хэш-код для строки s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* undef: удаление имени и определения из таблицы */
char undef(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
        {
            free((void *) np->name);
            free((void *) np->defn);
            np->name = 0;
            np->defn = 0;
            return 1; /* нашли */
        }
    return 0; /* не нашли */
}

/* lookup: ищет s */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* нашли */
    return NULL; /* не нашли */
}
