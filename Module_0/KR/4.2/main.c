
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define false 0
#define true !false

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

int main(void) {
    char text[] = "123.456E-6";
    double val = myatof(text);
    printf("Преобразованное значение через myatof: %g\n", val);
    printf("Преобразованное значение через atof:   %g\n", 123.456e-6);
    return 0;
}
