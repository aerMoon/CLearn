/*
 * Упражнение 2.7. Напишите функцию invert(х, р, n), возвращающую значение x с инвертированными
 * n битами, начиная с позиции p (остальные биты не изменяются).
 *
 */

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(void) {

	int test = invert(EOF, 4, 2);
	printf("EOF с инвертированными 2-я битами, начиная с 4-й позиции от нуля: %u", test);
    return 0;
}

unsigned invert(unsigned x, int p, int n) {

	for (int i = p; i < p + n; i++) {
		x = x ^ (1 << i);
	}
	return x;
}
