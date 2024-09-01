#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  double temp = 0;
  double dec_pow = pow(10, s21_get_pow(src));
  int sign = s21_get_bit(src.bits[3], 31);
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit_decimal(src, i) == 1) temp += pow(2, i);
  }
  temp /= dec_pow;
  if (sign) temp *= -1;
  *dst = (float)temp;
  return err;
}