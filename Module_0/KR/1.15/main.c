/*
 * Упражнение 1.15. Перепишите программу преобразования температур, выделив само преобразование в 
 * отдельную функцию.
 *
 */

#include <stdio.h>

double toCelsius(double fahr);

int main(void) {

    float fahr, celsius;
    int lower,  upper, step;

    lower = 0; /* нижняя граница таблицы температур */
    upper = 300; /* верхняя граница */
    step = 20; /* шаг */
    fahr = lower;

    printf("-------------\n| F  |   C  |\n-------------\n");
    while (fahr <= upper) {
		printf("|%3.0f |%6.1f|\n", fahr, toCelsius(fahr));
	    fahr = fahr + step;
	}
    printf("-------------\n");

	return 0;
}

double toCelsius(double fahr) {
	return ((5.0 / 9.0) * (fahr - 32.0));
}
