#include "s21_decimal.h"
// gcc s21_sub.c helper.c s21_is_greater_or_equal.c s21_is_greater.c
// s21_is_equal.c s21_add.c -g -o test

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = get_bit(value_1.bits[3], 31);  // считывание знаков
  int sign_2 = get_bit(value_2.bits[3], 31);
  set_bit(&value_1.bits[3], 31, 0);  // создание модулей чисел |a| и |b|
  set_bit(&value_2.bits[3], 31, 0);
  big_decimal BIG_value_1 = {0};
  big_decimal BIG_value_2 = {0};
  convertDecimalToBig(value_1, &BIG_value_1);
  convertDecimalToBig(value_2, &BIG_value_2);
  int flag = 0;
  int valueExp1 = extract_bits(value_1.bits[3], 16, 8);  // считывание степеней
  int valueExp2 = extract_bits(value_2.bits[3], 16, 8);
  int resultExp = valueExp1 >= valueExp2 ? valueExp1 : valueExp2;
  big_decimal temporary = {0};
  if (resultExp <= 28) {
    leveling(&BIG_value_1, &BIG_value_2);
    temporary.bits[7] = resultExp << 16;  // установка новой степени
    if (sign_1 != sign_2) {               // +- -+
      s21_add(value_1, value_2, result);
      set_bit(&result->bits[3], 31, sign_1);
    } else {  // ++ --
      if (sign_1 == 1)
        s21_sub(value_2, value_1, result);
      else {
        if (s21_is_greater_or_equal(value_1, value_2))
          sub_decimal(BIG_value_1, BIG_value_2, &temporary);
        else {
          sub_decimal(BIG_value_2, BIG_value_1, &temporary);
          set_bit(&temporary.bits[7], 31, 1);
        }
        convertBigToDecimal(temporary, result);
      }
    }
  } else
    flag = 2;
  return flag;
}