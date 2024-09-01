#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0;
  double temp = 0;
  double dec_pow = pow(10, s21_get_pow(src));
  int sign = s21_get_bit(src.bits[3], 31);
  s21_decimal dec_int_min = {0};
  s21_decimal dec_int_max = {0};
  s21_from_int_to_decimal(INT_MIN, &dec_int_min);
  s21_from_int_to_decimal(INT_MAX, &dec_int_max);
  if (s21_is_less(src, dec_int_min) || s21_is_greater(src, dec_int_max)) {
    err = 1;
  } else {
    for (int i = 0; i < 96; i++) {
      if (s21_get_bit_decimal(src, i) == 1) temp += pow(2, i);
    }
    temp /= dec_pow;
    if (sign) temp *= -1;
    *dst = (int)temp;
  }
  return err;
}