/*
 * Упражнение 1.20. Напишите программу detab, заменяющую символы табуляции во 
 * вводимом тексте нужным числом пробелов (до следующего "стопа" табуляции). 
 * Предполагается, что "стопы" табуляции расставлены на фиксированном расстоянии 
 * друг от друга, скажем, через n позиций. Как лучше задавать n — в виде значения
 * переменной или в виде именованной константы? 
 *
 */

#include <stdio.h>

int tabstop = 8;

int main(void) {

	int ch, pos = 0;
	extern int tabstop;

	while ((ch = getchar()) != EOF) {
	
		if (ch == '\t') {
			for (int i = pos; i < tabstop; i++) {
				putchar(' ');
			}
			pos = 0;
		} else if (ch == '\n') {
			pos = 0;
			putchar(ch);
		} else {
			++pos;
			if (pos > tabstop) {
				pos = 0;
			}
			putchar(ch);
		}
	} 
    return 0;
}
