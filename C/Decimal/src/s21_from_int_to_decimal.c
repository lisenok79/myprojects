#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int err = 0;
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
  if (src >= 0)
    dst->bits[0] = src;
  else if (src < 0) {
    dst->bits[0] = -src;
    s21_set_bit(&dst->bits[3], 1, 31);
  } else
    err = 1;
  return err;
}
