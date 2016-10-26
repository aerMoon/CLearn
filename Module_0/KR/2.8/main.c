/*
 * Упражнение 2.8. Напишите функцию rightrot(х, n), которая циклически сдвигает x вправо на n
 * разрядов.
 *
 */

#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n);
void printbin(unsigned x);

int main(void) {

	printf("101:\t\t");
	printbin(101);
	
	printf("101 >> 1:\t");
	printbin(101 >> 1);
	
	printf("101 << 1:\t");
	printbin(101 << 1);
	
	int test = rightrot(101, 5);

	printf("\nСдвигаем циклически 101 на 5 позиций вправо: %u\n", test);
	printbin(test);
    return 0;
}

unsigned rightrot(unsigned x, int n) {

	int pos = 0;
	while (pos++ < n) {
	
		int isZeroBitSet = x & 1;
		x = x >> 1;
		if (isZeroBitSet) {
			x = x | (1 << (sizeof(x) * 8 - 1));
		} else {
			x = x & ~(1 << (sizeof(x) * 8 - 1));
		}
	}
	return x;
}

void printbin(unsigned x) {

	for (int i = sizeof(x) * CHAR_BIT - 1; i >= 0; i--) {
	
		if (((i + 1) % 8) == 0)
			putchar(' ');
		if (((i + 1) % 4) == 0)
			putchar(' ');
		if (x & (1 << i)) {
			putchar('1');
		} else {
			putchar('0');
		}
	}
	putchar('\n');
}
