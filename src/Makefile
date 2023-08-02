OS := $(shell uname)

ifeq ($(OS),Darwin)
	CC = -Wall -Werror -Wextra
	FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
	OPEN_CMD = open
else
	CC = -Wall -Werror -Wextra
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
	OPEN_CMD = xdg-open
endif

all: clean gcov_report

s21_matrix.a:
	gcc $(CC) -c s21_*.c
	ar -crs s21_matrix.a s21_*.o

gcov_report: clean
	gcc $(CC) test*.c s21_*.c $(FLAGS) -o test
	./test
	lcov -t "./test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *gcda *.gco

clean:
	rm -rf *.o *.a test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info

rebuild: clean s21_matrix.a test

test: clean s21_matrix.a
	gcc $(CC) test*.c s21_matrix.a $(FLAGS) -lgcov -coverage -o test
	./test

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h

valgrind:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./test

leaks:
	leaks -atExit -- ./test