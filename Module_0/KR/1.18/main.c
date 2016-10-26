
/*
 * Упражнение 1.18. Напишите программу, которая будет в каждой вводимой строке 
 * заменять стоящие подряд символы пробелов и табуляций на один пробел и удалять 
 * пустые строки.
 *
 */

#include <stdio.h>

#define MAX_LEN 1024

int getLine(int outBuf[], int maxLen);
void clearBuf(int buf[], int len); 

#define FIRSTCHAR 1
#define TWOCHAR 2
#define SOMECHAR 0

int main(void) {

	int buf[MAX_LEN];
	int len, pos;

	clearBuf(buf, MAX_LEN);

	while ((len = getLine(buf, MAX_LEN)) != 0) {
		int status = SOMECHAR;
		for (int i = 0; i < len; i++) {
			if (status == SOMECHAR && (buf[i] == ' ' || buf[i] == '\t')) {		
				putchar(buf[i]);
				status = TWOCHAR;
			} else if ((status == TWOCHAR) && (buf[i] == ' ' || buf[i] == '\t')) {
				continue;
			} else {
				status = FIRSTCHAR;
				putchar(buf[i]);
			}			
		}
		putchar('\n');
	}
    return 0;
}

int getLine(int outBuf[], int maxLen) {

	// Получает строку из стандартного потока ввода
	
	int ch, pos = 0;	
	while ((ch = getchar()) != EOF) {
		if (ch == '\n')	
			break;
		outBuf[pos] = ch;
		++pos;
		if (pos > maxLen) {
			--pos;
			break;
		}
	}
	return pos;
}

void clearBuf(int buf[], int len) {

	// Очищает буфер

	for (int i = 0; i < len; i++) {
		buf[i] = 0;
	}
}
