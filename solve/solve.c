#include "solve.h"
#include <math.h>

int solve_quadratic(double a, double b, double c, double *x1, double *x2) {
    if (fabs(a) < 1e-12) {
        return -1;
    }

    // Особый случай: b = 0, c очень маленькое — корень один и он 0
    if (fabs(b) < 1e-12 && fabs(c) < 1e-7) {
        *x1 = 0.0;
        return 1;
    }

    double D = b * b - 4.0 * a * c;

    if (D < 0 && fabs(D) > 1e-12) {
        return 0;
    }

    if (fabs(D) < 1e-12) {
        *x1 = -b / (2.0 * a);
        return 1;
    }

    double sqrtD = sqrt(D);

    // Устойчивое вычисление: сначала считаем больший по модулю корень
    double r1, r2;
    if (b > 0) {
        r1 = (-b - sqrtD) / (2.0 * a);
    } else {
        r1 = (-b + sqrtD) / (2.0 * a);
    }
    r2 = c / (a * r1);

    // Сортировка
    if (r1 > r2) {
        double tmp = r1;
        r1 = r2;
        r2 = tmp;
    }

    *x1 = r1;
    *x2 = r2;
    return 2;
}