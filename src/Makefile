CC=g++
CFLAGS= -Wall -Wextra -Werror -std=c++17
PROGRAM_NAME=s21_matrix_oop.cpp
TEST_NAME=s21_matrix_oop_test.cpp
INCLUDE_LIBS=-lcheck -lrt -lpthread -lm
ERRORS=grep -v "0 errors" log.txt | grep -c errors | awk '{print $1}'

FORMATS_FOR_DEL=*.out *.gz *.o *.gch  log.txt logTest.txt  *dSYM coverage *.a *.gcda *gcno *.info Test *.cfg .clang-format 
all: clean test gcov_report


s21_matrix_oop.o: s21_matrix_oop.cpp s21_matrix_oop.h
	@$(CC) $(CFLAGS) s21_matrix_oop.cpp s21_matrix_oop.h -lm
	
s21_matrix_oop.a: s21_matrix_oop.o
	@ar -rcs s21_matrix_oop.a s21_matrix_oop.o
	@ranlib $@
	@cp $@ lib$@
	
clean:
	@rm -rf $(FORMATS_FOR_DEL)

OS = $(shell uname)
ifeq ($(OS), Linux)
	LINUX_LIBS=-lsubunit -lrt -lpthread -lm -lstdc++
	CC += -D OS_LINUX -g
	CHECK_LEAKS=valgrind --leak-check=full -s --log-file=log.txt
	OPEN_GCOV=firefox coverage$(PWD)/index.html
	OUT_LEAKS= grep log.txt
else
	LINUX_LIBS=
	CC += -D OS_MAC
	CHECK_LEAKS=CK_FORK=no leaks --atExit --
	OPEN_GCOV=open coverage/index.html
endif

test:	clean style 
	@$(CC) -g $(PROGRAM_NAME) $(TEST_NAME) -lgtest $(LINUX_LIBS) -o ./Test 
	@$(CHECK_LEAKS) ./Test
	@echo -n "leaks = "
	@ $(ERRORS)

style: 
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -n *.cpp *.h
	@rm -rf .clang-format

gcov_report: clean style 
	@$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -pthread $(PROGRAM_NAME) $(TEST_NAME) -lgtest -o Test
	# @$(CC) -fprofile-arcs -lgtest -ftest-coverage --coverage $(PROGRAM_NAME) $(TEST_NAME) -o Test -lcheck $(LINUX_LIBS) $(GCOV)
	@./Test
	@lcov -c -d . -o coverage.info
	@genhtml coverage.info -o coverage
	@$(OPEN_GCOV)


