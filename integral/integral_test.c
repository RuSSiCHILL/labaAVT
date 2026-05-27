#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>

#include "integral.h"

static int tests_passed = 0;
static int tests_failed = 0;

void check(const char *name, int condition) {
    if (condition) {
        printf("[PASS] %s\n", name);
        tests_passed++;
    } else {
        printf("[FAIL] %s\n", name);
        tests_failed++;
    }
}

/* Вспомогательные тестовые функции */
static double f_const(double x) {
    (void)x;
    return 1.0;
}

static double f_linear(double x) {
    return x;
}

static double f_quadratic(double x) {
    return x * x;
}

static double f_cubic(double x) {
    return x * x * x;
}

int main(void) {
    double result;
    const double eps = 1e-9;

    /* 1. Константная функция: ∫[0,10] 1 dx = 10 */
    result = trapezoidal_integration(f_const, 0.0, 10.0, 100);
    check("constant function ∫[0,10] 1 dx", fabs(result - 10.0) < eps);

    /* 2. Линейная функция n=1: ∫[0,10] x dx = 50 */
    result = trapezoidal_integration(f_linear, 0.0, 10.0, 1);
    check("linear function n=1", fabs(result - 50.0) < eps);

    /* 3. Линейная функция n=100: ∫[0,10] x dx = 50 */
    result = trapezoidal_integration(f_linear, 0.0, 10.0, 100);
    check("linear function n=100", fabs(result - 50.0) < eps);

    /* 4. Квадратичная функция n=1000: ∫[0,10] x² dx = 1000/3 */
    result = trapezoidal_integration(f_quadratic, 0.0, 10.0, 1000);
    check("quadratic function n=1000", fabs(result - 1000.0 / 3.0) < 1e-2);

    /* 5. Квадратичная функция n=100000: ∫[0,10] x² dx = 1000/3 */
    result = trapezoidal_integration(f_quadratic, 0.0, 10.0, 100000);
    check("quadratic function n=100000", fabs(result - 1000.0 / 3.0) < 1e-6);

    /* 6. Кубическая функция: ∫[0,10] x³ dx = 2500 */
    result = trapezoidal_integration(f_cubic, 0.0, 10.0, 100000);
    check("cubic function", fabs(result - 2500.0) < 1e-4);

    /* 7. Тригонометрическая функция: ∫[0,π] sin(x) dx = 2 */
    result = trapezoidal_integration(sin, 0.0, M_PI, 10000);
    check("sin(x) on [0, π]", fabs(result - 2.0) < 1e-6);

    /* 8. Совпадающие пределы → 0 */
    result = trapezoidal_integration(f_const, 5.0, 5.0, 100);
    check("equal bounds", fabs(result) < eps);

    /* 9. n == 0 → 0 */
    result = trapezoidal_integration(f_const, 0.0, 10.0, 0);
    check("zero intervals (n=0)", fabs(result) < eps);

    /* 10. Обратный порядок пределов: ∫[10,0] x dx = -50 */
    result = trapezoidal_integration(f_linear, 10.0, 0.0, 100);
    check("reversed bounds", fabs(result - (-50.0)) < eps);

    /* 11. Отрицательный отрезок: ∫[-5,5] x² dx = 250/3 */
    result = trapezoidal_integration(f_quadratic, -5.0, 5.0, 100000);
    check("symmetric interval [-5, 5]", fabs(result - 250.0 / 3.0) < 1e-6);

    /* 12. Малый отрезок с плавающей точкой */
    result = trapezoidal_integration(f_const, 1e-10, 2e-10, 10);
    check("small float interval", fabs(result - 1e-10) < 1e-20);

    /* Итог */
    printf("\n%d passed, %d failed\n", tests_passed, tests_failed);
    return tests_failed > 0 ? 1 : 0;
}