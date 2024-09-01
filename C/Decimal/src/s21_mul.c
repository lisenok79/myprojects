#include "s21_decimal.h"
// gcc s21_mul.c helper.c -g -o test
// int main(){
//     s21_decimal src1={0};
//     s21_decimal src2={0};
//     s21_decimal result={0};
//   // 79 228 162 514 264 337 593 543 950 335
//   // 79 228 162 514 264 337 593 543.950 335
//   src1.bits[0] = 0b11111111111111111111111111111111;
//   src1.bits[1] = 0b11111111111111111111111111111111;
//   src1.bits[2] = 0b11111111111111111111111111111111;
//   src1.bits[3] = 0b10000000000000000000000000000000;

//   src2.bits[0] = 0b00000000000000000000000000000100;
//   src2.bits[1] = 0b00000000000000000000000000000000;
//   src2.bits[2] = 0b00000000000000000000000000000000;
//   src2.bits[3] = 0b00000000000000000000000000000000;

//   s21_mul(src1,src2,&result);
//     return 0;
// }

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal BIG_value_1 = {0};
  big_decimal BIG_value_2 = {0};
  convertDecimalToBig(value_1, &BIG_value_1);
  convertDecimalToBig(value_2, &BIG_value_2);
  int sign_1 = get_bit(value_1.bits[3], 31);  // считывание знаков
  int sign_2 = get_bit(value_2.bits[3], 31);
  int flag = 0;
  int valueExp1 = extract_bits(value_1.bits[3], 16, 8);  // считывание степеней
  int valueExp2 = extract_bits(value_2.bits[3], 16, 8);
  int resultExp = valueExp1 + valueExp2;
  big_decimal res = {0};
  if (resultExp <= 28) {
    mul_decimal(BIG_value_1, BIG_value_2, &res);
    set_bit(&res.bits[7], 31, sign_1 == sign_2 ? 0 : 1);
    flag = convertBigToDecimal(res, result);
  } else
    flag = 2;
  return flag;
}
