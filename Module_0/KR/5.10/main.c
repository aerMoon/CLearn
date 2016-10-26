/*
 * Упражнение 5.10. Напишите программу expr, интерпретирующую обратную польскую запись выражения,
 * задаваемого командной строкой, в которой каждый оператор и операнд представлены отдельным аргументом.
 * Например,
 *
 *      expr 2 3 4 + *
 *
 * вычисляется так же, как выражение 2 х (3 + 4).
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define false 0
#define true !false

#define MAXITEMS 20
#define MAXLINE 1000

/* atof: преобразование строки s в double */
double myatof (char s[]) // Стандарт 11 не позволяет перекрывать так имена ибо atof есть в math.h
{
    double val, power;
    int i, sign;
    for (i = 0; isspace (s[i]); i++)
        ; /* игнорирование левых символов-разделителей */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit (s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] =='.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    // Устанавливаем степень числа через е
    int powerDig = 0;
    if (tolower(s[i]) == 'e') {
        int powerSing = true;
        ++i;
        if (s[i] == '-') {
            powerSing = false;
            ++i;
        } else if (s[i] == '+') {
            ++i;
        }
        while (isdigit(s[i])) {
            powerDig *= 10;
            if (powerSing) {
                powerDig += s[i] - '0';
            } else {
                powerDig -= s[i] - '0';
            }
            ++i;
        }
    }
    return sign * val / power * pow(10, powerDig);
}

int isdouble(char *s)
{
    char ch, ischar = false;
    int pos = 0;
    while ((ch = *(s + pos++)) != 0) {
        if (ch != '.' && !isdigit(ch))
            return false;
        if (ch == '-') {
            ischar = true;
        }
    }
    if (ischar)
        return false;
    return true;
}

int main(int argc, char *argv[])
{
    int cnt_numbers = 0;
    double numbers[MAXITEMS];
    int cnt_operations = 0;
    char operations[MAXITEMS];

    // Убираем имя программы из аргументов
    argv++;
    argc--;

    // Разбираем на составляющие
    while (argc-- > 0) {
        if (isdouble(*argv)) {
            numbers[cnt_numbers++] = myatof(*argv);
        } else {
            if (*argv[0] == '\\' ) {

                operations[cnt_operations++] = *argv[2];
                continue;
            }
            operations[cnt_operations++] = *argv[0];
        }
        argv++;
    }

    // Считаем
    --cnt_numbers;
    int curr = 0;
    while (cnt_operations--) {

        double left_val = numbers[cnt_numbers];
        double right_val = numbers[cnt_numbers - 1];
        --cnt_numbers;

        switch (operations[curr++]) {
            case '-':
                numbers[cnt_numbers] = left_val - right_val;
                printf("%.8g - %.8g = %.8g\n", left_val, right_val, numbers[cnt_numbers]);
                break;
            case '+':
                numbers[cnt_numbers] = left_val + right_val;
                printf("%.8g + %.8g = %.8g\n", left_val, right_val, numbers[cnt_numbers]);
                break;
            case '*':
                numbers[cnt_numbers] = left_val * right_val;
                printf("%.8g * %.8g = %.8g\n", left_val, right_val, numbers[cnt_numbers]);
                break;
            case '/':
                numbers[cnt_numbers] = left_val / right_val;
                printf("%.8g / %.8g = %.8g\n", left_val, right_val, numbers[cnt_numbers]);
                break;
            default:
                printf("Неизвестная операция - ");
                putchar(operations[curr]);
                putchar('\n');
                break;
        }
    }

    return 0;
}
