#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = get_bit(value_1.bits[3], 31);  // считывание знаков
  int sign_2 = get_bit(value_2.bits[3], 31);
  int flag = 0;
  int valueExp1 = extract_bits(value_1.bits[3], 16, 8);  // считывание степеней
  int valueExp2 = extract_bits(value_2.bits[3], 16, 8);
  int resultExp = valueExp2 - valueExp1;
  s21_decimal quotient = {0};  // структура для хранения частного
  s21_decimal remainder = {0};  // структура для хранения остатка
  s21_decimal res = {0};
  s21_decimal ten = {{10, 0, 0, 0}};
  if (empty(value_2) == 0) {
    if (resultExp >= 0 ||
        -resultExp <= 28) {  // степень в диапозоне довзоленной
      div_decimal(value_1, value_2, &quotient, &remainder);  // деление мантис
      gorging(quotient, remainder, value_2, &res);
      resultExp -= extract_bits(res.bits[3], 16, 8);
      if (resultExp > 0 || -resultExp <= 28) {
        if (resultExp <= 0) {
          setexp(&res, -resultExp);
          copy(result, res);
        } else {
          for (int i = 0; i < resultExp; i++) s21_mul(ten, ten, &ten);
          s21_mul(res, ten, result);
        }
        set_bit(&result->bits[3], 31,
                sign_1 == sign_2 ? 0 : 1);  // установка знака
      } else
        flag = 2;
    } else
      flag = 2;  // слишком маленькое число
  } else
    flag = 3;  // деление на ноль
  return flag;
}
