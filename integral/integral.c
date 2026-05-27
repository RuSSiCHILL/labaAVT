#include "integral.h"

double trapezoidal_integration(double (*f)(double), double a, double b, unsigned int n) {
    if (n == 0) {
        return 0.0;
    }

    /* Обработка обратного порядка пределов: интеграл от a до b при a > b
     * равен -интегралу от b до a */
    double sign = 1.0;
    if (a > b) {
        double tmp = a;
        a = b;
        b = tmp;
        sign = -1.0;
    }

    /* Совпадающие пределы — интеграл равен нулю */
    if (a == b) {
        return 0.0;
    }

    /* Шаг интегрирования. При очень малых (b-a) или очень больших n
     * возможна потеря значимости, но для типа double это крайний случай */
    const double h = (b - a) / n;

    /* Метод трапеций:
     *   Integral ≈ h * (0.5*f(a) + Σ f(x_i) + 0.5*f(b))
     *
     * При большом n стандартное последовательное суммирование
     * накапливает ошибку округления. Используем компенсационное
     * суммирование (алгоритм Кэхэна) для повышения точности. */
    double sum = 0.0;
    double compensation = 0.0;  /* Потерянный младший разряд */

    /* 0.5 * f(a) */
    double y = 0.5 * f(a) - compensation;
    double t = sum + y;
    compensation = (t - sum) - y;
    sum = t;

    /* 0.5 * f(b) */
    y = 0.5 * f(b) - compensation;
    t = sum + y;
    compensation = (t - sum) - y;
    sum = t;

    for (unsigned int i = 1; i < n; i++) {
        /* Точка разбиения: a + i*h.
         * При больших i накапливается ошибка O(ε·i), что приемлемо
         * для большинства практических задач с double. */
        const double x = a + i * h;

        y = f(x) - compensation;
        t = sum + y;
        compensation = (t - sum) - y;
        sum = t;
    }

    return sign * sum * h;
}