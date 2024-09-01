#include "tests.h"

#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0

int main() {
  int fc = 1;
  runTest(greater_lib_suite(), &fc);
  runTest(less_lib_suite(), &fc);
  runTest(equal_lib_suite(), &fc);
  runTest(less_or_equal_lib_suite(), &fc);
  runTest(greater_or_equal_lib_suite(), &fc);
  runTest(not_equal_lib_suite(), &fc);

  runTest(sub_lib_suite(), &fc);
  runTest(add_lib_suite(), &fc);
  runTest(mul_lib_suite(), &fc);
  runTest(div_lib_suite(), &fc);

  runTest(from_decimal_to_float_lib_suite(), &fc);
  runTest(from_float_to_decimal_lib_suite(), &fc);
  runTest(from_decimal_to_int_lib_suite(), &fc);
  runTest(from_int_to_decimal_lib_suite(), &fc);

  runTest(negate_lib_suite(), &fc);
  runTest(truncate_lib_suite(), &fc);
  runTest(round_lib_suite(), &fc);
  runTest(floor_lib_suite(), &fc);

  return fc;
}

void runTest(Suite *suit, int *fc) {
  SRunner *sr = srunner_create(suit);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  int f = srunner_ntests_failed(sr);
  if (*fc != 0) *fc = f;
  srunner_free(sr);
}
