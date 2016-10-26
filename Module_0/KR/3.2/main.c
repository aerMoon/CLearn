/*
 * Упражнение 3.2. Напишите функцию escape(s, t), которая при копировании 
 * текста из t в s преобразует такие символы, как новая строка и табуляция 
 * в "видимые последовательности символов" (вроде \n и \t).
 * Используйте инструкцию switch. Напишите функцию, выполняющую обратное 
 * преобразование эскейп-последовательностей в настоящие символы.
 *
 */

#include <stdio.h>

void unescape(char s[], char t[]) {

	int pos_s, pos_t;
	pos_s = pos_t = 0;
	while (s[pos_s] != '\0') {
		switch (s[pos_s]) {
			case '\\':
				if (s[++pos_s] == 't')
					t[pos_t++] = '\t';
				else
					t[pos_t++] = '\n';
				break;
			default:
				t[pos_t++] = s[pos_s];
				break;
		}
		++pos_s;
	}
	t[pos_t++] = '\0';
}

void escape(char s[], char t[]) {

	int pos_s, pos_t;
    pos_s = pos_t = 0;
	while (s[pos_s] != '\0') {
	
		switch (s[pos_s]) {
		
			case '\t': 
				t[pos_t++] = '\\';
				t[pos_t++] = 't';
				break;
			case '\n': 
				t[pos_t++] = '\\';
				t[pos_t++] = 'n';
				break;
			default:
				t[pos_t++] = s[pos_s];
				break;
		}
		++pos_s;
	}
	t[pos_t++] = '\0';
}

void print(char s[]) {

	int pos = 0;
	while (s[pos] != '\0') {
		putchar(s[pos++]);
	}
}

int main(void) {
	
	char text[] = "Hello\tnew\nWorld!!!";
	char dest[1024];
	char dest2[1024];
	
	escape(text, dest);
	print(dest);
    putchar('\n');

	unescape(dest, dest2);
	print(dest2);
	putchar('\n');
	return 0;
}
