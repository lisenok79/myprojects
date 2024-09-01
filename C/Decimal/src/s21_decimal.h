#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct decimal {
  int bits[4];
} s21_decimal;

typedef struct big {
  int bits[8];  // 7 байтов для маантисы
} big_decimal;

typedef union {
  int ui;
  float fl;
} fbits;

// арифмитические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // a+b
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // a-b
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // a*b
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// операторы сравнения
int s21_is_less(s21_decimal value_1, s21_decimal value_2);              // a<b
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);     // a<=b
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);           // a>b
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);  // a>=b
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);             // a==b
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);         // a!=b
// остаток

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

//вспомогательные функции
int decimal_multi(big_decimal *value_1, int value);  // бигдецимал на число
int decimal_shift_left(big_decimal *src, int a);
int extract_bits(int num, int start, int n);
void set_bit(int *num, int position, int value);
int get_bit(int num, int n);
int sum_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result);
void convertDecimalToBig(s21_decimal value, big_decimal *result);
int convertBigToDecimal(big_decimal value, s21_decimal *result);
void leveling(
    big_decimal *value_1,
    big_decimal *value_2);  // выравненивание по степеням двух бигдецималов
void setEXP(big_decimal *value, int exp);  // установка степени для биг децимала
void setexp(s21_decimal *value, int exp);  // установка степени для децимала
int emptyDECIMAL(big_decimal value);  // проверка на пустой ,бигдецимал
void sub_decimal(big_decimal value_1, big_decimal value_2, big_decimal *result);
int overflowDecimal(big_decimal value);  // проверка на ппереполнене децимала
void div_decimal(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *quotient,
                 s21_decimal *remainder);  // делит мантисы децималов
void mul_decimal(big_decimal value_1, big_decimal value_2,
                 big_decimal *result);  // бигдецимал умножает на бигдецимал
int most_bit_BIG(big_decimal value);  //  позиция старшего бита биг децимала
int most_bit(s21_decimal value);  //позиция старшего бита децимала
void decimal_shift_right(big_decimal *src, int a);  //сдвиг вправо бигдецимл
void shift_right(s21_decimal *src, int a);  //сдвиг вправо децимл
int shift_left(s21_decimal *src, int a);    //сдвиг влево децимл
int empty(s21_decimal value);  // проверка на пустой децимал
void copy(s21_decimal *result, s21_decimal value);  //  копирует value в result
int get_bit_decimal(s21_decimal value,
                    int position);  //  получает любой бит из децимала
void addition(s21_decimal *result, s21_decimal value,
              int k);  // дополняет результат деления
void gorging(s21_decimal quotient, s21_decimal remainder, s21_decimal value,
             s21_decimal *result);  // объеденение целого и частного
void div_BIGdecimal(big_decimal value_1, int a, big_decimal *result);
int equal_BIG(big_decimal value1, big_decimal value2);
int greater_BIG(big_decimal value1, big_decimal value2);
int greater_or_equal_BIG(big_decimal value1, big_decimal value2);
int get_bit_BIGdecimal(big_decimal value, int position);
void addition_BIG(big_decimal *result, big_decimal value, int k);
void copy_BIG(big_decimal *result, big_decimal value);
void delTen(s21_decimal *value);

//вспомогательные функции Алекс
int s21_get_bit(int value, int position);
int s21_get_bit_decimal(s21_decimal value, int position);
int s21_set_bit(int *value, int bit, int position);
void s21_set_bit_decimal(s21_decimal *value, int bit, int position);
int s21_get_pow(s21_decimal value);
s21_decimal *set_scale(s21_decimal *value, int scale);
int get_exp(float *value);