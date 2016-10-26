/*
 *
 * Упражнение 5.9. Перепишите программы day_of_year и month_day, используя вместо индексов
 * указатели.
 *
 */

#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: определяет день года по месяцу и дню */
int day_of_year(int year, int month, int day)
{
    if (year < 0)
        return - 1;
    int i, leap;
    leap = (year%4 == 0) && (year%100 != 0 || year%400 == 0);
    if (daytab[leap][month] < day || day < 0)
        return -1;

    // Ну ок, используем указатели
    char *ptr = &daytab[leap][1];
    for (i = 1; i < month; i++)
        //day += daytab[leap][i];
        day += *(ptr + i*sizeof(char));

    return day;
}
/* month_day: определяет месяц и день по дню года */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    *pmonth = -1;
    *pday = -1;
    if (year < 0)
        return;
    int i, leap;
    leap = (year%4 == 0) && (year%100 != 0 || year%400 == 0);
    if (yearday < 0 || (leap == 0 && yearday > 365) || (leap == 1 && yearday > 366))
        return;
    // Такая же песня с индексом
    char *ptr = &daytab[leap][0];
    for (i = 1; yearday > *(ptr + i*sizeof(char)) /* daytab[leap][i]*/; i++)
        yearday -= *(ptr + i*sizeof(char)) /*daytab[leap][i]*/;
    *pmonth = i;
    *pday = yearday;
}

int main(void) {
    int m, d;
    month_day( 1988, 366, &m, &d);
    printf(">> month_day\nmonth:\t%d\nday:\t%d\n\n", m, d);
    printf(">> day_of_year\nday:\t%d\n\n", day_of_year(1988, 12, 31));
    return 0;
}
