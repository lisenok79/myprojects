#include "s21_decimal.h"
int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int sign = get_bit(value.bits[3], 31);
  if (sign == 0)
    res = s21_truncate(value, result);
  else {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal quotient = value;
    s21_decimal remainder = {0};
    s21_decimal null = {0};
    int r = 0;
    int exp = extract_bits(value.bits[3], 16, 8);
    int sign = get_bit(value.bits[3], 31);
    if (empty(value) == 0) {
      setexp(&quotient, 0);
      set_bit(&quotient.bits[3], 31, 0);
      for (int i = 0; i < exp; i++)
        div_decimal(quotient, ten, &quotient, &remainder);
      s21_from_decimal_to_int(remainder, &r);
      if (r != 0) s21_add(quotient, one, &quotient);
      copy(result, quotient);
      set_bit(&result->bits[3], 31, sign);
      setexp(result, 0);
    } else
      copy(result, null);
  }
  return res;
}