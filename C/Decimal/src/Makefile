GCC = gcc -Wall -Werror -Wextra -std=c11 
TESTFLAGS = -lcheck
RM = rm -rf
CP= cp -R
CLF = clang-format
OCAT = -o
.C = *.c

all: s21_decimal.a

s21_decimal.a:
	$(GCC) -c $(.C)
	ar rc s21_decimal.a *.o
	mkdir binary_files
	mv *.o binary_files

test: clean s21_decimal.a
	$(GCC) $(TESTFLAGS) -I/Users/$(USER)/.brew/include -L/Users/$(USER)/.brew/lib tests/*.c s21_decimal.a -o s21_test
	./s21_test

clean:
	$(RM) binary_files s21_test gcovreport *.a *.o *.gcno *.gcda *.info binary_files report test

clang:
	$(CP) ../materials/linters/.$(CLF) .$(CLF)
	$(CLF) -n *.c *.h
	$(CLF) -i *.c *.h
	$(RM) .$(CLF)

gcov_report:
	$(GCC) --coverage -lcheck -I/Users/$(USER)/.brew/include -L/Users/$(USER)/.brew/lib $(.C) tests/*.c -o gcovreport \
	`pkg-config --cflags --libs check`
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	open report/index.html
