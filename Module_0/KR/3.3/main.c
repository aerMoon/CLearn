/*
 * Упражнение 3.3. Напишите функцию expand(s1, s2), заменяющую сокращенную 
 * запись наподобие a-z в строке s1 эквивалентной полной записью 
 * abc. . . xyz в s2. В s1 допускаются буквы (прописные и строчные) и
 * цифры. Следует уметь справляться с такими случаями, как a-b-c, 
 * a-z0-9 и -а-b. Считайте знак - в начале или в конце s1 обычным 
 * символом минус.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define BUF_SIZE 1024

int isdigitInText(int ch) {
    return ch >= '0' && ch <= '9';
}

int ischarInText(int ch) {
    return tolower(ch) >= 'a' && tolower(ch) <= 'z';
}

void expand(char s1[], char s2[]) {

    int pos_s1, pos_s2;
    pos_s1 = pos_s2	= 0;
	while (s1[pos_s1] != '\0') {
        if (s1[pos_s1] == '-') {
            // Проверка на число
            if (isdigitInText(s1[pos_s1 - 1]) && isdigitInText(s1[pos_s1 + 1])) {
                for (int i = s1[pos_s1 - 1]; i <= s1[pos_s1 + 1]; i++) {
                    s2[pos_s2++] = i;
                }
                s2[pos_s2++] = s1[pos_s1 += 2];
            // Проверка на символы
            } else if (ischarInText(s1[pos_s1 - 1]) && ischarInText(s1[pos_s1 + 1]) && fabs(s1[pos_s1 + 1] - s1[pos_s1 - 1]) > 1) {
                for (int i = s1[pos_s1 - 1]; i <= s1[pos_s1 + 1]; i++) {
                    s2[pos_s2++] = i;
                }
                s2[pos_s2++] = s1[pos_s1 += 2];
            }
        }
        s2[pos_s2++] = s1[pos_s1++];
    }
}

int main(void) {
	char text[] = "a-z\n0-9\na-b-c\na-z0-9\n-a-b\n"; 
	char buffer[BUF_SIZE];
	expand(text, buffer);
	int p = 0;
	while (buffer[p] != '\0') {
        putchar(buffer[p++]);
	}
    return 0;
}
