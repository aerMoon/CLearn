
/*
 * Упражнение 1.9. Напишите программу, копирующую символы ввода в выходной поток и 
 * заменяющую стоящие подряд пробелы на один пробел.
 *
 */

#include <stdio.h>

#define false 0
#define true 1

void main() {

	int ch;
	char isLastSpace = false;

	while ((ch = getchar()) != EOF) {
		if (ch == ' ') {
			if (isLastSpace == false) {
				isLastSpace = true;
				putchar(ch);
			}
		} else {
			isLastSpace = false;
			putchar(ch);
		}
	}
}
