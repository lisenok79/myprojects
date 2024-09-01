CC = gcc

# NCURSES = -lncurses
CFLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -lcheck -lpthread -lm
ADD_FLAGS = -lm -lncurses
GCOV_FLAGS_TEMP :=
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

MATRIX_SOURCE = libs/*.c
MATRIX_OBJECTS = libs/*.o
MATRIX_LIB = char_matrix.a

OS:=$(shell uname -s)
ifeq ($(OS), Linux)
 TEST_FLAGS += -lrt -lsubunit
 ADD_FLAGS += -lrt -pthread -lsubunit
endif

TETRIS_SRC = brick_game/tetris/*.c 
OBJECTS = *.o
BUILD_DIR = build
DIST_DIR = s21_tetris
EXECUTABLE_NAME = tetris_game.exe

MAIN = brick_game/tetris/tetris.c

LOGIC_SOURCE = brick_game/tetris/backend.c
LOGIC_H = brick_game/tetris/*.h
LOGIC_OBJECTS = brick_game/tetris/backend.o
LOGIC_LIB_NAME = s21_tetris.a

INTERFACE_SOURCE = gui/cli/frontend.c
INTERFACE_H = gui/cli/*.h
INTERFACE_OBJECTS = gui/cli/frontend.o
INTERFACE_LIB_NAME = s21_cli.a

TEST_H = tests/*.h*
TEST_SOURCE = tests/*.c
TEST_OBJECTS = tests/*.o
TEST_EXECUTABLE_NAME = ttrs_test
GCOV_REPORT_NAME = $(TEST_EXECUTABLE_NAME)_gcov_report
REPORT_LIB = gcov_report
CHECK_LIB = -lcheck

CLANG = clang-format

.C = *.c
BACK_PATH = brick_game/tetris/
FRONT_PATH = gui/cli/

.PHONY: all install uninstall clean dvi dist 

all: 

install: clean_exe s21_tetris.a s21_cli.a
	$(CC) $(CFLAGS) $(MAIN) $(BUILD_DIR)/s21_tetris.a $(BUILD_DIR)/s21_cli.a -o $(BUILD_DIR)/$(EXECUTABLE_NAME) $(ADD_FLAGS)
	./$(BUILD_DIR)/$(EXECUTABLE_NAME)

uninstall: 
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME)

dvi: clean_dvi create_build_dir
	doxygen Doxyfile
	open build/docs/html/index.html
	
dist: clean_dist create_build_dir
	mkdir -p $(BUILD_DIR)/$(DIST_DIR)
	cp -rf brick_game $(BUILD_DIR)/$(DIST_DIR)/brick_game
	cp -rf gui $(BUILD_DIR)/$(DIST_DIR)/gui
	cp -rf Makefile $(BUILD_DIR)/$(DIST_DIR)/
	cp -rf Doxyfile $(BUILD_DIR)/$(DIST_DIR)/
	tar -czf $(BUILD_DIR)/$(DIST_DIR).tar.gz -C $(BUILD_DIR) $(DIST_DIR)
	rm -rf $(BUILD_DIR)/$(DIST_DIR)


s21_tetris.a: clean_obj create_build_dir $(LOGIC_OBJECTS)
	ar rc $(BUILD_DIR)/$@ $(LOGIC_OBJECTS)
	@make -s clean_obj

s21_cli.a: clean_obj create_build_dir $(INTERFACE_OBJECTS)
	ar rc $(BUILD_DIR)/$@ $(INTERFACE_OBJECTS)
	@make -s clean_obj

%.o: %.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS_TEMP) -c $< -o $@

clean_obj:
	rm -f $(LOGIC_OBJECTS) $(INTERFACE_OBJECTS)

clean_libs:
	rm -f $(BUILD_DIR)/$(LOGIC_LIB_NAME) $(BUILD_DIR)/$(INTERFACE_LIB_NAME)

clean_exe:
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME)

clean_dvi:
	rm -rf build/docs/

clean_dist:
	rm -rf $(BUILD_DIR)/$(DIST_DIR).*


clean: clean_obj clean_libs clean_exe clean_dvi clean_dist
	rm -rf build
	rm -rf a.out

create_build_dir:
	mkdir -p $(BUILD_DIR)

s21_matrix.a:
	$(CC) $(CFLAGS) -c $(MATRIX)
	ar rcs s21_matrix.a $(OBJECTS)
	ranlib s21_matrix.a

clang_n:
	cp ../materials/linters/.clang-format ../src/.clang-format 
	$(CLANG) -style=Google -n $(LOGIC_SOURCE) $(INTERFACE_SOURCE)
	rm -rf .clang-format

clang_i:
	cp ../materials/linters/.clang-format ../src/.clang-format 
	$(CLANG) -style=Google -i $(LOGIC_SOURCE) $(INTERFACE_SOURCE)
	rm -rf .clang-format

dop:
	$(CC) $(CFLAGS) $(BACK_PATH)$(.C) $(FRONT_PATH)$(.C) -g -lncurses -lm
	./a.out
# valgrind: s21_tetris.a s21_cli.a
# 	$(CC) $(CFLAGS) $(LOGIC_SOURCE) $(INTERFACE_SOURCE) $(TEST_SOURCE) $(BUILD_DIR)/$(LOGIC_LIB_NAME) $(BUILD_DIR)/$(INTERFACE_LIB_NAME) $(MATRIX_LIB) $(ADD_FLAGS) $(CHECK_LIB) -o valgrind
# 	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./valgrind

# test: clean_test_exe create_build_dir s21_tetris.a s21_cli.a
# 	$(CC) $(CFLAGS) $(LOGIC_SOURCE) $(INTERFACE_SOURCE) $(TEST_SOURCE) $(BUILD_DIR)/$(LOGIC_LIB_NAME) $(BUILD_DIR)/$(INTERFACE_LIB_NAME) $(MATRIX_LIB) $(ADD_FLAGS) $(CHECK_LIB) -o $(BUILD_DIR)/$(TEST_EXECUTABLE_NAME)
# 	@make -s clean_obj
# 	./$(BUILD_DIR)/$(TEST_EXECUTABLE_NAME)

# gcov_report: clean_test_exe clean_gcov_test create_build_dir s21_tetris.a s21_cli.a
# 	$(CC) $(CFLAGS) --coverage $(LOGIC_SOURCE) $(INTERFACE_SOURCE) $(TEST_SOURCE) $(BUILD_DIR)/$(LOGIC_LIB_NAME) $(BUILD_DIR)/$(INTERFACE_LIB_NAME) $(MATRIX_LIB) $(ADD_FLAGS) $(CHECK_LIB) -o $(BUILD_DIR)/$(TEST_EXECUTABLE_NAME)
# 	@make -s clean_obj
# 	./$(BUILD_DIR)/$(TEST_EXECUTABLE_NAME)
# 	lcov -t "$(GCOV_REPORT_NAME)" -o $(BUILD_DIR)/$(GCOV_REPORT_NAME).info -c -d .
# 	genhtml -o $(BUILD_DIR)/$(REPORT_LIB)/html_info $(BUILD_DIR)/$(GCOV_REPORT_NAME).info
# 	@make -s clean_gcov_test
# 	open $(BUILD_DIR)/$(REPORT_LIB)/html_info/index.html

# clean_test_exe:
# 	rm -f $(BUILD_DIR)/$(TEST_EXECUTABLE_NAME)
# 	rm -f $(BUILD_DIR)/$(GCOV_REPORT_NAME)

# clean_gcov_test:
# 	rm -f *.gcno */*.gcno */*/*.gcno */*/*/*.gcno */*/*/*/*.gcno
# 	rm -f *.gcov */*.gcov */*/*.gcov */*/*/*.gcov */*/*/*/*.gcov
# 	rm -f *.info */*.info */*/*.info */*/*/*.info */*/*/*/*.info
# 	rm -f *.gcda */*.gcda */*/*.gcda */*/*/*.gcda */*/*/*/*.gcda
# 	# rm $(BUILD_DIR)/$(GCOV_REPORT_NAME).info

# clean_gcov_test_exe:
# 	rm -rf $(BUILD_DIR)/$(REPORT_LIB)