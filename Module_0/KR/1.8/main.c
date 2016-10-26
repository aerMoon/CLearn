/*
 * Упражнение 1.8. Напишите программу для подсчета пробелов, табуляций
 * и новых строк.
 *
 */

#include <stdio.h>

void main() {
	int countSpaces = 0;
    int	countTabs = 0;
    int	countLines = 0;
	int ch; 

	while ((ch = getchar()) != EOF) {
		if (ch == ' ')
			++countSpaces;
		if (ch == '\t')
			++countTabs;
		if (ch == '\n')
			++countLines;
	}
	printf("Пробелов:\t%d\nТабов:\t%d\nСтрок:\t%d\n", countSpaces, countTabs, countLines);
}

