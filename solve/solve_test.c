#include "solve.h"
#include <math.h>
#include <stdio.h>

int tests_passed = 0;
int tests_failed = 0;

void check(const char *name, int condition) {
    if (condition) {
        printf("[PASS] %s\n", name);
        tests_passed++;
    } else {
        printf("[FAIL] %s\n", name);
        tests_failed++;
    }
}

int main(void) {
    double x1, x2;
    int n;

    // 1. Нулевой коэффициент a
    n = solve_quadratic(0, 1, 1, &x1, &x2);
    check("a = 0 returns -1", n == -1);

    // 2. Положительный дискриминант: x^2 - 1 = 0  ->  [-1, 1]
    n = solve_quadratic(1, 0, -1, &x1, &x2);
    check("D > 0: two roots", n == 2);
    check("D > 0: x1 = -1", fabs(x1 + 1.0) < 1e-9);
    check("D > 0: x2 = 1", fabs(x2 - 1.0) < 1e-9);

    // 3. Нулевой дискриминант: x^2 = 0  ->  [0]
    n = solve_quadratic(1, 0, 0, &x1, &x2);
    check("D = 0: one root", n == 1);
    check("D = 0: x1 = 0", fabs(x1) < 1e-9);

    // 4. Отрицательный дискриминант: x^2 + 1 = 0  ->  []
    n = solve_quadratic(1, 0, 1, &x1, &x2);
    check("D < 0: no roots", n == 0);

    // 5. c = -1E-7, корни ~[-3E-4, 3E-4], точность 4 знака
    n = solve_quadratic(1, 0, -1e-7, &x1, &x2);
    check("c = -1e-7: two roots", n == 2);
    check("c = -1e-7: x1 ~ -3e-4", fabs(x1 + 3e-4) < 1e-4);
    check("c = -1e-7: x2 ~ 3e-4", fabs(x2 - 3e-4) < 1e-4);

    // 6. Большие числа, точность 11 знака
    n = solve_quadratic(1, -1e+10, -1, &x1, &x2);
    check("big numbers: two roots", n == 2);
    check("big numbers: x1 ~ -1e-10", fabs(x1 + 1e-10) < 1e-10);
    check("big numbers: x2 ~ 1e+10", fabs(x2 - 1e+10) < 1e-9);

    // 7. c = -1E-8, корень [0], точность 7 знака
    n = solve_quadratic(1, 0, -1e-8, &x1, &x2);
    check("c = -1e-8: one root", n == 1);
    check("c = -1e-8: x1 ~ 0", fabs(x1) < 1e-7);

    printf("\nTotal: %d passed, %d failed\n", tests_passed, tests_failed);
    return tests_failed > 0 ? 1 : 0;
}