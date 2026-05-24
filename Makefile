CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11

.PHONY: all clean format-check format test

all: test

clean:
	rm -rf *.o *.a *_test
	rm -rf solve/*.o solve/*.a solve/solve_test
	rm -rf stack/*.o stack/*.a stack/stack_test

format-check:
	clang-format --dry-run --Werror $$(find . -name "*.c" -o -name "*.h")

format:
	clang-format -i $$(find . -name "*.c" -o -name "*.h")

# --- solve ---

solve/solve.o: solve/solve.c solve/solve.h
	$(CC) $(CFLAGS) -c solve/solve.c -o solve/solve.o

solve/solve.a: solve/solve.o
	ar rc solve/solve.a solve/solve.o

solve/solve_test.o: solve/solve_test.c solve/solve.h
	$(CC) $(CFLAGS) -c solve/solve_test.c -o solve/solve_test.o

solve/solve_test: solve/solve_test.o solve/solve.a
	$(CC) $(CFLAGS) -static -o solve/solve_test solve/solve_test.o solve/solve.a -lm

# --- stack ---

stack/stack.o: stack/stack.c stack/stack.h
	$(CC) $(CFLAGS) -c stack/stack.c -o stack/stack.o

stack/stack.a: stack/stack.o
	ar rc stack/stack.a stack/stack.o

stack/stack_test.o: stack/stack_test.c stack/stack.h
	$(CC) $(CFLAGS) -c stack/stack_test.c -o stack/stack_test.o

stack/stack_test: stack/stack_test.o stack/stack.a
	$(CC) $(CFLAGS) -static -o stack/stack_test stack/stack_test.o stack/stack.a

# --- test ---

test: solve/solve_test stack/stack_test
	@for t in $$(find . -name "*_test" -type f ! -name "*.c" ! -name "*.o"); do \
		echo "Running $$t..."; \
		./$$t || exit 1; \
	done