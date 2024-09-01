GPP = c++ -Wall -Werror -Wextra -std=c++17 
TESTFLAGS = -lgtest -lgmock -lgmock_main -lgtest_main -pthread
RM = rm -rf
CP= cp -R
CLF = clang-format
OCAT = -o
.C = *.cpp

all: s21_matrix_oop.a

s21_matrix_oop.a:
	$(GPP) -c $(.C)
	ar rc s21_matrix_oop.a *.o
	mkdir binary_files
	mv *.o binary_files

test: clean s21_matrix_oop.a
	$(GPP) $(TESTFLAGS) -I/Users/$(USER)/.brew/include -L/Users/$(USER)/.brew/lib tests/*.cpp s21_matrix_oop.a -o s21_test
	./s21_test

clean:
	$(RM) binary_files s21_test gcovreport *.a *.o *.gcno *.gcda *.info binary_files report test

clang:
	$(CP) ../materials/linters/.$(CLF) .$(CLF)
	$(CLF) -n *.cpp *.h
	$(CLF) -i *.cpp *.h
	$(RM) .$(CLF)

gcov_report:
	$(GPP) --coverage -lcheck -I/Users/$(USER)/.brew/include -L/Users/$(USER)/.brew/lib $(.C) tests/*.c -o gcovreport \
	`pkg-config --cflags --libs check`
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	open report/index.html

dop: cldop
	$(GPP) *.cpp -g -o dop
	./dop

cldop:
	rm -rf dop