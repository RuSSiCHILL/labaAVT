#include "stack.h"

void stack_init(Stack *s) {
    s->top = -1;
}

int stack_is_empty(Stack *s) {
    return s->top == -1;
}

int stack_push(Stack *s, int value) {
    if (s->top >= STACK_MAX - 1) return -1;
    s->data[++(s->top)] = value;
    return 0;
}

int stack_pop(Stack *s, int *value) {
    if (stack_is_empty(s)) return -1;
    *value = s->data[(s->top)--];
    return 0;
}