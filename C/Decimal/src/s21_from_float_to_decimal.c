#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int sign = 0, err = 0, exp = get_exp(&src), scale = 0;
  double tmp = src;
  if ((fabs(src) > 0 && fabs(src) < 1e-28f) ||
      fabs(src) > 79228162514264337593543950335.f || isnan(src) || isinf(src))
    err = 1;
  else {
    for (int i = 0; i < 4; i++) dst->bits[i] = 0;

    if (src < 0) {
      tmp *= -1;
      src *= -1;
      sign = 1;
    }

    while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
      tmp *= 10;
      scale++;
    }

    if (scale <= 28 && (exp > -94 && exp < 96)) {
      fbits mant = {0};
      tmp = (float)tmp;
      for (; fmod(tmp, 10) == 0 && scale > 0; scale--) tmp /= 10;
      mant.fl = tmp;
      exp = get_exp(&mant.fl);
      s21_set_bit_decimal(dst, 1, exp);
      for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
        if ((mant.ui & (1 << j)) != 0) {
          s21_set_bit_decimal(dst, 1, i);
        }
      }
      set_scale(dst, scale);
      if (sign) s21_set_bit(&dst->bits[3], 1, 31);
    }
  }
  return err;
}