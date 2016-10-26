#ifndef CALC_H
#define CALC_H

#define false 0
#define true !false

#define NUMBER '0' /* признак числа */

void push (double);
double pop (void);
int getop (char []);
int getch(void);
void ungetch(int);

#endif // CALC_H

