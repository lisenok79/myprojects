#include "s21_decimal.h"

// gcc s21_add.c s21_sub.c s21_is_greater_or_equal.c s21_is_equal.c helper.c
// s21_is_greater.c s21_mul.c helperBIG.c -g -o test

// int main(){
//   s21_decimal result={0};
//   long int tmp1 = 4294967295;
//   int tmp2 = (1 << 31);
//   s21_decimal dec1 = {{tmp1, tmp1, tmp1, tmp2}};
//   s21_decimal dec2 = {{1, 0, 0, tmp2}};
//   s21_add(dec1,dec2,&result);
//   s21_print_decimal(result);

//     return 0;
// }

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal BIG_value_1 = {0};
  big_decimal BIG_value_2 = {0};
  convertDecimalToBig(value_1, &BIG_value_1);
  convertDecimalToBig(value_2, &BIG_value_2);
  int sign_1 = get_bit(value_1.bits[3], 31);  // считывание знаков
  int sign_2 = get_bit(value_2.bits[3], 31);
  int flag = 0;
  int valueExp1 = extract_bits(value_1.bits[3], 16, 8);  // считывание степеней
  int valueExp2 = extract_bits(value_2.bits[3], 16, 8);
  int resultExp = valueExp1 >= valueExp2 ? valueExp1 : valueExp2;
  big_decimal temporary = {0};
  if (resultExp <= 28) {
    leveling(&BIG_value_1, &BIG_value_2);
    temporary.bits[7] = resultExp << 16;  // установка новой степени
    if (sign_1 == sign_2) {               // -- ++
      sum_decimal(BIG_value_1, BIG_value_2, &temporary);  // подсчет мантисы
      set_bit(&temporary.bits[7], 31, sign_1);  // устоновка знака
      flag = convertBigToDecimal(temporary, result);
    } else {  // функция вычитания
      if (sign_1 == 0) {
        set_bit(&value_2.bits[3], 31, 0);
        s21_sub(value_1, value_2, result);  // +-
      } else {
        set_bit(&value_1.bits[3], 31, 0);
        s21_sub(value_2, value_1, result);  //-+
      }
    }
  } else
    flag = 2;
  return flag;
}
