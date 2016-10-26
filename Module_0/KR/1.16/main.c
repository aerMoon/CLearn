
/* 
 * Упражнение 1.16. Перепишите main предыдущей программы так, чтобы она могла 
 * печатать самую длинную строку без каких-либо ограничений на ее размер. 
 *
 */

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[]); 
void copy(char to[], char from[]);

/* печать самой длинной строки */ 
int main(void) {
	int len; /* длина текущей строки */
	int max; /* длина максимальной из просмотренных строк */
	char line[MAXLINE]; /* текущая строка */
	char longest[MAXLINE]; /* самая длинная строка */
	max = 0;
	while ((len = getline(line)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}	
	if (max > 0) /* была ли хоть одна строка? */ 
		printf("%s", longest);  
    return 0;
}

/* getline: читает строку в s, возвращает длину */
int getline(char s[])
{
	int c, i;
	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == 'n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: копирует из 'from' в 'то'; to достаточно большой  */
void copy(char to[], char from[])
{
	int i = 0;
	while ((to[i] =from[i]) != '\0')
		++i;
}
