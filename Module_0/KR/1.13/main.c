
/*
 * Упражнение 1.13. Напишите программу, печатающую гистограммы длин вводимых слов. Гистограмму легко 
 * рисовать горизонтальными полосами. Рисование вертикальными полосами — более трудная задача.
 *
 */

#include <stdio.h>

#define IN 1
#define OUT 0

void main() {

	char inWord = OUT;
	int len_word = 0;
	int ch;

	while ((ch = getchar()) != EOF) {
	
		if (ch == ' ' || ch == '\t' || ch == '\n')
		{
			if (inWord == IN) {
				for (int i = 0; i < len_word; i++) {
					putchar('-');
				}
				putchar('\n');
				len_word = 0;
			} 
			inWord = OUT;
		} else {
			inWord = IN;
			++len_word;
		}
	}
}
