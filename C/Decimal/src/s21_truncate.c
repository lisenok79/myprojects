#include "s21_decimal.h"
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  s21_decimal null = {0};
  s21_decimal ten = {{10, 0, 0, 0}};
  int sign = get_bit(value.bits[3], 31);
  int exp = extract_bits(value.bits[3], 16, 8);
  if (empty(value))
    copy(result, null);
  else {
    for (int i = 0; i < exp; i++) div_decimal(value, ten, &value, NULL);
    copy(result, value);
    set_bit(&result->bits[3], 31, sign);
  }
  return res;
}