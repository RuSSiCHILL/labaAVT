#ifndef SOLVE_H
#define SOLVE_H

// Возвращает количество корней (0, 1, 2) или -1 при ошибке (a = 0)
// Корни записываются в x1 и x2, отсортированы по возрастанию
int solve_quadratic(double a, double b, double c, double *x1, double *x2);

#endif