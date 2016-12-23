/*
 * Упражнение 6.5. Напишите функцию undef, удаляющую имя и определение из таблицы, организация которой поддерживается
 * функциями lookup и install.
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

int main(void) {

    // Надо заполнить таблицу и написать undef
    return 0;
}

/* install: заносит имя и текст (name, defn) в таблицу */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* не найден */
        np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
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

/* lookup: ищет s */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* нашли */
    return NULL; /* не нашли */
}
