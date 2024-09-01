#include "s21_decimal.h"

void div_BIGdecimal(
    big_decimal value_1, int a,
    big_decimal *result) {  // делит биг децимл на int без остатка
  big_decimal res = {0};
  big_decimal value_2 = {{a, 0, 0, 0, 0, 0, 0, 0}};
  setEXP(&value_1, 0);               // убираем степень
  set_bit(&value_1.bits[7], 31, 0);  // получаем модуль
  int Mbit1 = most_bit_BIG(value_1);  // считываем количество бит
  int Mbit2 = most_bit_BIG(value_2);
  if (equal_BIG(value_1, value_2))
    result->bits[0] = 1;                     // если числа равны
  else if (greater_BIG(value_1, value_2)) {  // если первое больше второго
    int k = Mbit2;                           // текущий индекс
    big_decimal Ntemp = value_1;
    decimal_shift_right(&Ntemp, Mbit1 - k);
    while (Mbit1 >= k) {
      decimal_shift_left(&res, 1);
      if (greater_or_equal_BIG(Ntemp, value_2)) {
        set_bit(&res.bits[0], 0, 1);
        sub_decimal(Ntemp, value_2, &Ntemp);
        if (Mbit1 > k) {
          k++;
          addition_BIG(&Ntemp, value_1, Mbit1 - k);
        }
      } else if (Mbit1 == k)
        break;
      else {
        k++;
        addition_BIG(&Ntemp, value_1, Mbit1 - k);
      }
    }
    // copy(remainder,Ntemp);// запись остатка
    copy_BIG(result, res);
  }
  // else copy(remainder,value_1);
}

void setEXP(big_decimal *value, int exp) {
  int sign = get_bit(value->bits[7], 31);
  value->bits[7] = exp << 16;
  set_bit(&value->bits[7], 31, sign);
}

void leveling(big_decimal *value_1, big_decimal *value_2) {
  int valueExp1 = extract_bits(value_1->bits[7], 16, 8);
  int valueExp2 = extract_bits(value_2->bits[7], 16, 8);
  int resultEXP = valueExp1 >= valueExp2 ? valueExp1 : valueExp2;
  int delt = valueExp1 - valueExp2 >= 0 ? valueExp1 - valueExp2
                                        : -(valueExp1 - valueExp2);
  if (delt != 0) {
    for (int i = 0; i < delt; i++) {
      if (valueExp1 > valueExp2)
        decimal_multi(value_2, 10);
      else
        decimal_multi(value_1, 10);
    }
    if (valueExp1 > valueExp2)
      setEXP(value_2, resultEXP);
    else
      setEXP(value_1, resultEXP);
  }
}

int decimal_multi(big_decimal *value_1,
                  int value) {  // умножаем  бигдецимал на обычный int
  int flag = 1;
  int count = 0;
  big_decimal result = {0};
  while (value != 0) {
    big_decimal temporary = *value_1;
    if ((value & 1) != 0) {
      decimal_shift_left(&temporary, count);
      sum_decimal(result, temporary, &result);
    }
    value >>= 1;
    count++;
  }
  if (flag == 1)
    for (int i = 0; i < 7; i++) value_1->bits[i] = result.bits[i];
  return flag ? 0 : 1;  // 0-ок 1-слишком большое число
}

int sum_decimal(big_decimal value_1, big_decimal value_2,
                big_decimal *result) {  // скалыдвает мантисы двух бигдецималов
  big_decimal temporary = {0};
  int overflow = 0;
  for (int i = 0; i < 7; i++) {  // цикл по всем интам
    int res = 0;
    for (int k = 0; k < 32; k++) {
      int bit_1 = get_bit(value_1.bits[i], k);
      int bit_2 = get_bit(value_2.bits[i], k);
      if (overflow == 0) {  // переполнения нет
        if (bit_1 != bit_2)
          set_bit(&res, k, 1);  // 10 01 ->1
        else if (bit_1 == 1)
          overflow = 1;        // 11 ->0
      } else {                 // переполнение есть
        if (bit_1 == bit_2) {  // 11 00 ->1
          overflow = bit_1;
          set_bit(&res, k, 1);
        }  // все другие случаи 01 10 ->0
      }
    }
    temporary.bits[i] = res;
  }
  if (overflow == 0)
    for (int i = 0; i < 7; i++) result->bits[i] = temporary.bits[i];
  int flag = overflow;
  return flag;  // 0-все окей 1-все плохо
}

int overflowDecimal(
    big_decimal value) {  // проверка выходит ли биг децимал за пределы децимал
  int overflow = 0;
  for (int i = 3; i < 6; i++) {
    if (value.bits[i] != 0) {
      overflow = 1;
      break;
    }
  }
  return overflow;  // 0-нет 1-да
}

int emptyDECIMAL(big_decimal value) {  // проверка на пустой бигдецимал
  int result = 1;
  for (int i = 0; i < 7; i++) {
    if (value.bits[i] != 0) {
      result = 0;
      break;
    }
  }
  return result;  // 0-децимал не нулевой
}

int most_bit_BIG(big_decimal value) {  // старший бит биг децимала
  int result = 0;
  int flag = 0;
  for (int i = 6; i >= 0; i--) {
    if (flag) break;
    for (int k = 31; k >= 0; k--) {
      if (get_bit(value.bits[i], k)) {
        result = i * 32 + k;
        flag = 1;
        break;
      }
    }
  }
  return result;
}

void decimal_shift_right(big_decimal *src, int a) {  //сдвиг вправо бигдецимл
  big_decimal BigTemporary = *src;
  for (int k = 0; k < a; k++) {  // сдвиг на n равносилен свдигу на 1 n раз
    unsigned int b = BigTemporary.bits[0];
    BigTemporary.bits[0] = b >> 1;
    for (int i = 1; i < 7; i++) {
      b = BigTemporary.bits[i];
      if (get_bit(BigTemporary.bits[i], 0))
        set_bit(&BigTemporary.bits[i - 1], 31, 1);
      BigTemporary.bits[i] = b >> 1;
    }
  }
  for (int i = 0; i < 7; i++) src->bits[i] = BigTemporary.bits[i];
}

int decimal_shift_left(big_decimal *src, int a) {  //сдвиг влево бигдецимл
  big_decimal temporary = *src;
  int last_flag = 0;
  int flag = 0;
  int overflow = 0;
  for (int k = 0; k < a; k++) {  // сдвиг на n равносилен свдигу на 1 n раз
    last_flag = get_bit(temporary.bits[0], 31);
    temporary.bits[0] <<= 1;
    if (overflow) break;
    for (int i = 1; i < 7; i++) {
      flag = get_bit(temporary.bits[i], 31);
      temporary.bits[i] <<= 1;
      if (last_flag) set_bit(&temporary.bits[i], 0, 1);
      last_flag = flag;
    }
    if (flag == 1) overflow = 1;
  }
  if (flag == 0)
    for (int i = 0; i < 7; i++) src->bits[i] = temporary.bits[i];
  return flag;  // 0-ок число 1-все плохо
}

int equal_BIG(big_decimal value1,
              big_decimal value2) {  // равны ли мантисы бигдецималов
  int result = 1;
  for (int i = 6; i >= 0; i--) {
    if (value1.bits[i] != value2.bits[i]) {
      result = 0;
      break;
    }
  }
  return result;  // 1-да 0-нет
}

int greater_BIG(big_decimal value1,
                big_decimal value2) {  // больше ли мантиса бигдецимл
  int result = 0;
  for (int i = 6; i >= 0; i--) {
    unsigned int a = value1.bits[i];
    unsigned int b = value2.bits[i];
    if (a > b) {
      result = 1;
      break;
    }
  }
  return result;  // 1-да 0-нет
}

int greater_or_equal_BIG(big_decimal value1,
                         big_decimal value2) {  // больше либо равен бигдецимл
  int result = 0;
  if (greater_BIG(value1, value2) || equal_BIG(value1, value2)) result = 1;
  return result;  // 1-да 0-нет
}

void mul_decimal(big_decimal value_1, big_decimal value_2,
                 big_decimal *result) {  // умножает биг децимал на бигдецимал
  int shift = 0;
  big_decimal res = {0};
  for (int i = 0; i < 7; i++) {
    int a = value_2.bits[i];
    for (int k = 0; k < 32; k++) {
      big_decimal temp = value_1;
      int bit = get_bit(a, k);
      if (bit) {
        decimal_shift_left(&temp, shift);
        sum_decimal(res, temp, &res);
      }
      shift++;
    }
  }
  for (int i = 0; i < 7; i++) result->bits[i] = res.bits[i];
}

void sub_decimal(
    big_decimal value_1, big_decimal value_2,
    big_decimal *result) {  // вычитание модулей двух децималово,обязательно
                            // подавать value_1>value_2
  int flag = 0;
  for (int i = 0; i < 7; i++) {
    int a = value_1.bits[i];
    int b = value_2.bits[i];
    int res = 0;
    for (int k = 0; k < 32; k++) {
      int bit_a = get_bit(a, k);
      int bit_b = get_bit(b, k);
      if (flag == 0) {
        if (bit_a != bit_b) {  // 01 10
          set_bit(&res, k, 1);
          flag = bit_b;
        }
      } else {  // 11 00
        if (bit_a == 0)
          set_bit(&res, k, bit_b ? 0 : 1);
        else {
          set_bit(&res, k, bit_b);
          flag = bit_b;
        }
      }
    }
    result->bits[i] = res;
  }
}
int get_bit_BIGdecimal(big_decimal value,
                       int position) {  //  получает любой бит из децимала
  int i = position / 32;
  int b = position - i * 32;
  return get_bit(value.bits[i], b);
}

void addition_BIG(big_decimal *result, big_decimal value,
                  int k) {  // нужно только для деления
  decimal_shift_left(result, 1);
  set_bit(&result->bits[0], 0, get_bit_BIGdecimal(value, k));
}

void copy_BIG(big_decimal *result, big_decimal value) {
  if (result)
    for (int i = 0; i < 8; i++) result->bits[i] = value.bits[i];
}