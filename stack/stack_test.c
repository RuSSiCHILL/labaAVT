#include "stack.h"
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
    Stack s;
    int val;

    stack_init(&s);

    check("New stack is empty", stack_is_empty(&s) == 1);
    check("Pop from empty returns -1", stack_pop(&s, &val) == -1);

    check("Push 10 returns 0", stack_push(&s, 10) == 0);
    check("Not empty after push", stack_is_empty(&s) == 0);

    check("Push 20 returns 0", stack_push(&s, 20) == 0);
    check("Push 30 returns 0", stack_push(&s, 30) == 0);

    check("Pop returns 0", stack_pop(&s, &val) == 0);
    check("Popped value is 30", val == 30);

    check("Pop returns 0", stack_pop(&s, &val) == 0);
    check("Popped value is 20", val == 20);

    check("Pop returns 0", stack_pop(&s, &val) == 0);
    check("Popped value is 10", val == 10);

    check("Empty after popping all", stack_is_empty(&s) == 1);
    check("Pop from empty returns -1", stack_pop(&s, &val) == -1);

    for (int i = 0; i < STACK_MAX; i++) {
        stack_push(&s, i);
    }
    check("Push to full stack returns -1", stack_push(&s, 999) == -1);

    printf("\nTotal: %d passed, %d failed\n", tests_passed, tests_failed);
    return tests_failed > 0 ? 1 : 0;
}