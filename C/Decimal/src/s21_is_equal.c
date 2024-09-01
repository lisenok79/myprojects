#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  if (s21_is_greater(value_1, value_2) == 1 ||
      s21_is_greater(value_2, value_1) == 1)
    result = 0;
  return result;
}