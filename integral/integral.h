#ifndef INTEGRAL_H
#define INTEGRAL_H

/**
 * Вычисляет определенный интеграл методом трапеций.
 *
 * @param f Указатель на подынтегральную функцию double -> double
 * @param a Нижний предел интегрирования
 * @param b Верхний предел интегрирования
 * @param n Количество разбиений отрезка [a, b]
 * @return Приближенное значение интеграла
 */
double trapezoidal_integration(double (*f)(double), double a, double b, unsigned int n);

#endif