CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11

.PHONY: all clean format-check format test

all: test

clean:
	rm -rf *.o *.a *_test
	rm -rf solve/*.o solve/*.a solve/solve_test
	rm -rf stack/*.o stack/*.a stack/stack_test
	rm -rf integral/*.o integral/*.a integral/integral_test
    rm -rf list/*.o list/*.a list/list_test

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

# --- integral ---

integral/integral.o: integral/integral.c integral/integral.h
	$(CC) $(CFLAGS) -c integral/integral.c -o integral/integral.o

integral/integral.a: integral/integral.o
	ar rc integral/integral.a integral/integral.o

integral/integral_test.o: integral/integral_test.c integral/integral.h
	$(CC) $(CFLAGS) -c integral/integral_test.c -o integral/integral_test.o

integral/integral_test: integral/integral_test.o integral/integral.a
	$(CC) $(CFLAGS) -static -o integral/integral_test integral/integral_test.o integral/integral.a -lm

# --- list ---

list/list.o: list/list.c list/list.h
	$(CC) $(CFLAGS) -c list/list.c -o list/list.o

list/list.a: list/list.o
	ar rc list/list.a list/list.o

list/list_test.o: list/list_test.c list/list.h
	$(CC) $(CFLAGS) -c list/list_test.c -o list/list_test.o

list/list_test: list/list_test.o list/list.a
	$(CC) $(CFLAGS) -static -o list/list_test list/list_test.o list/list.a

# --- test ---

test: solve/solve_test stack/stack_test integral/integral_test list/list_test
	@for t in $$(find . -name "*_test" -type f ! -name "*.c" ! -name "*.o"); do \
		echo "Running $$t..."; \
		./$$t || exit 1; \
	done
