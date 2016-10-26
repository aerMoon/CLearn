/*
 * Упражнение 1.12. Напишите программу, которая печатает содержимое своего ввода, помещая по одному
 * слову на каждой строке.
 *
 */

#include <stdio.h>

#define IN 1
#define OUT 0

void main() {
	int c;
	char inWord = OUT;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (inWord == IN) {
				printf("\n");
			}
			inWord = OUT;
		} else {
			inWord = IN;
			putchar(c);
		}
	}
}

