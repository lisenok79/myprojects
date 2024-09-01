#include "s21_decimal.h"

// int main() {
//     s21_decimal value = {0};
//     s21_decimal result = {0};
//     value.bits[0] = 0b00000000000000000101001011110010;
//     value.bits[1] = 0b00000000000000000000000000000000;
//     value.bits[2] = 0b00000000000000000000000000000000;
//     value.bits[3] = 0b10000000000001000000000000000000;
//     s21_negate(value, &result);
//     s21_print_decimal(result);
//     return 0;
// }

int s21_negate(s21_decimal value, s21_decimal *result) {
  int err = 0;
  *result = value;
  if (result) {
    if (s21_get_bit(value.bits[3], 31) == 1) {
      s21_set_bit(&result->bits[3], 0, 31);
    } else {
      s21_set_bit(&result->bits[3], 1, 31);
    }
  } else {
    err = 1;
  }
  return err;
}