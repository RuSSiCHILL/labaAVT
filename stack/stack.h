#ifndef STACK_H
#define STACK_H

#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;
} Stack;

void stack_init(Stack *s);
int stack_is_empty(Stack *s);
int stack_push(Stack *s, int value);
int stack_pop(Stack *s, int *value);

#endif