#ifndef SRC_TESTS_H
#define SRC_TESTS_H

#include <check.h>
#include <math.h>

#include "../s21_decimal.h"

#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0

Suite *greater_lib_suite();
Suite *less_lib_suite();
Suite *equal_lib_suite();
Suite *less_or_equal_lib_suite();
Suite *greater_or_equal_lib_suite();
Suite *not_equal_lib_suite();
Suite *sub_lib_suite();
Suite *add_lib_suite();
Suite *mul_lib_suite();
Suite *div_lib_suite();
Suite *from_decimal_to_float_lib_suite();
Suite *from_float_to_decimal_lib_suite();
Suite *from_decimal_to_int_lib_suite();
Suite *from_int_to_decimal_lib_suite();
Suite *negate_lib_suite();
Suite *truncate_lib_suite();
Suite *round_lib_suite();
Suite *floor_lib_suite();

void runTest(Suite *suit, int *fc);

#endif  //  SRC_TESTS_H