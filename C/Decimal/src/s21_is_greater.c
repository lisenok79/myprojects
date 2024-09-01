#include "s21_decimal.h"

// gcc s21_is_greater.c helper.c -g -o test

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  big_decimal BIG_value_1 = {0};
  big_decimal BIG_value_2 = {0};
  convertDecimalToBig(value_1, &BIG_value_1);
  convertDecimalToBig(value_2, &BIG_value_2);
  leveling(&BIG_value_1, &BIG_value_2);
  int result = -1;  // false
  if (emptyDECIMAL(BIG_value_1) == 0 || emptyDECIMAL(BIG_value_2) == 0) {
    if (value_1.bits[3] >> 31 != value_2.bits[3] >> 31) {  // a>0 b<0 || a<0 b>0
      if (value_1.bits[3] >> 31 == 0)
        result = 1;  // a>0 b<0
      else
        result = 0;                           // a<0 b>0
    } else if (value_1.bits[3] >> 31 == 0) {  // a>0 b>0
      for (int i = 6; i >= 0; i--) {  // сравниваем мантисы
        int a = BIG_value_1.bits[i];
        int b = BIG_value_2.bits[i];
        if (a == b) continue;
        if (result == 1 || result == 0)
          break;  // нашли различие выходим из  внешнего цикла
        for (int i = 31; i >= 0; i--) {
          int bit1 = get_bit(a, i);
          int bit2 = get_bit(b, i);
          if (bit1 != bit2) {
            result = bit1;
            break;
          }
        }
      }
      result = (result == -1) ? 0 : result;
    } else {  // a<0 b<0
      s21_decimal copy_value1 = value_1;
      s21_decimal copy_value2 = value_2;
      set_bit(&copy_value1.bits[3], 31, 0);
      set_bit(&copy_value2.bits[3], 31, 0);
      result = s21_is_greater(copy_value2, copy_value1);
    }
  } else
    result = 0;
  return result;  // 0-false 1-true
}
