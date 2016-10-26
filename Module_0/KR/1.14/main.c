/*
 * Упражнение  1.14. Напишите  программу,  печатающую  гистограммы частот  встречаемости  вводимых 
 * символов.
 *
 */

#include <stdio.h>

void main() {

	// Так как ещё не раболи с русскими символа, то буду использовать стандартный ANSI 
	int ansi[256];
	int ch;

	// Чистим
	for (int i = 0; i < 256; i ++) {
		ansi[i] = EOF;
	}
	
	// Заполняем
	while ((ch = getchar()) != EOF){
		if (ansi[ch] == EOF) {
			ansi[ch] = 1;	
		} else {
			++ansi[ch];
		}
	}
	putchar('\n');

	// Выводим
	for (int i = 0; i < 256; i++)
	{
		if (ansi[i] == EOF) {
			continue;	
		}
		if (i == '\t') {
			printf("\\t");
		} else if (i == '\n') {
			printf("\\n");
		} else {
			putchar(i);
		}
		putchar(':');
		for (int j = 0; j < ansi[i]; j++){
			putchar('-');
		}
		putchar('\n');
	}
}
