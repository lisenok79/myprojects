#include "s21_decimal.h"

void gorging(s21_decimal quotient, s21_decimal remainder, s21_decimal value,
             s21_decimal *result) {  // объеденение целого и частного
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal temp_REM = {0};
  s21_decimal temp_RES = {0};
  copy(result, quotient);
  int k = 0;
  if (empty(remainder) == 0) {
    do {
      s21_mul(*result, ten, result);
      s21_mul(remainder, ten, &remainder);
      div_decimal(remainder, value, &remainder, &temp_REM);
      if (s21_add(*result, remainder, &temp_RES) == 0) {
        copy(result, temp_RES);
        copy(&remainder, temp_REM);
      } else
        break;
      k++;
    } while (k != 28 && empty(temp_REM) == 0);
    setexp(result, k);
  }
}

int empty(s21_decimal value) {  // пустой ли децимал
  int result = 1;
  for (int i = 0; i < 3; i++) {
    if (value.bits[i] != 0) {
      result = 0;
      break;
    }
  }
  return result;  // 0-децимал не нулевой
}

void shift_right(s21_decimal *src, int a) {  //сдвиг вправо децимл
  s21_decimal temporary = *src;
  for (int k = 0; k < a; k++) {  // сдвиг на n равносилен свдигу на 1 n раз
    unsigned int b = temporary.bits[0];
    temporary.bits[0] = b >> 1;
    for (int i = 1; i < 3; i++) {
      b = temporary.bits[i];
      if (get_bit(temporary.bits[i], 0)) set_bit(&temporary.bits[i - 1], 31, 1);
      temporary.bits[i] = b >> 1;
    }
  }
  for (int i = 0; i < 3; i++) src->bits[i] = temporary.bits[i];
}

int shift_left(s21_decimal *src, int a) {  //сдвиг влево децимл
  s21_decimal temporary = *src;
  int last_flag = 0;
  int flag = 0;
  int overflow = 0;
  for (int k = 0; k < a; k++) {  // сдвиг на n равносилен свдигу на 1 n раз
    last_flag = get_bit(temporary.bits[0], 31);
    temporary.bits[0] <<= 1;
    if (overflow) break;
    for (int i = 1; i < 3; i++) {
      flag = get_bit(temporary.bits[i], 31);
      temporary.bits[i] <<= 1;
      if (last_flag) set_bit(&temporary.bits[i], 0, 1);
      last_flag = flag;
    }
    if (flag == 1) overflow = 1;
  }
  if (flag == 0)
    for (int i = 0; i < 3; i++) src->bits[i] = temporary.bits[i];
  return flag;  // 0-ок число 1-все плохо
}

void copy(s21_decimal *result,
          s21_decimal value) {  //  копирует value в result для децималов
  if (result)
    for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
}

int get_bit_decimal(s21_decimal value,
                    int position) {  //  получает любой бит из децимала
  int i = position / 32;
  int b = position - i * 32;
  return get_bit(value.bits[i], b);
}
void addition(s21_decimal *result, s21_decimal value,
              int k) {  // нужно только для деления
  // int Mbit1=most_bit(value);
  shift_left(result, 1);
  set_bit(&result->bits[0], 0, get_bit_decimal(value, k));
}

void div_decimal(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *quotient,
                 s21_decimal *remainder) {  // делит мантис децимл
  s21_decimal res = {0};
  s21_decimal null = {0};
  setexp(&value_1, 0);  // убираем степени
  setexp(&value_2, 0);
  set_bit(&value_1.bits[3], 31, 0);  // получаем модули
  set_bit(&value_2.bits[3], 31, 0);
  int Mbit1 = most_bit(value_1);  // считываем количество бит
  int Mbit2 = most_bit(value_2);
  if (s21_is_equal(value_1, value_2))
    quotient->bits[0] = 1;  // если числа равны
  else if (s21_is_greater(value_1, value_2)) {  // если первое больше второго
    int k = Mbit2;                              // текущий индекс
    s21_decimal Ntemp = value_1;
    shift_right(&Ntemp, Mbit1 - k);
    while (1) {
      shift_left(&res, 1);
      if (s21_is_greater_or_equal(Ntemp, value_2)) {
        set_bit(&res.bits[0], 0, 1);
        s21_sub(Ntemp, value_2, &Ntemp);
        if (Mbit1 != k) {
          k++;
          addition(&Ntemp, value_1, Mbit1 - k);
        } else
          break;
      } else if (Mbit1 != k) {
        k++;
        addition(&Ntemp, value_1, Mbit1 - k);
      } else
        break;
    }
    copy(remainder, Ntemp);  // запись остатка
    copy(quotient, res);     // запись целого
  } else {
    copy(remainder, value_1);
    copy(quotient, null);
  }
}

int most_bit(s21_decimal value) {  // старший бит децимал
  int result = 0;
  int flag = 0;
  for (int i = 2; i >= 0; i--) {
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

void convertDecimalToBig(s21_decimal value,
                         big_decimal *result) {  // из децимал в бигдецимал
  for (int i = 0; i < 3; i++)
    result->bits[i] = value.bits[i];  // копирование мантисы
  result->bits[7] = value.bits[3];  // копирование технической части
}

int convertBigToDecimal(big_decimal value,
                        s21_decimal *result) {  // из бигдецимал в децимал
  s21_decimal empty = {0};
  // s21_decimal ten={10};
  int overflow = overflowDecimal(value);
  int flag = 0;
  int sign = get_bit(value.bits[7], 31);
  if (overflow == 0) {
    // delTen(&value);
    for (int i = 0; i < 3; i++) result->bits[i] = value.bits[i];
    result->bits[3] = value.bits[7];
  } else {
    int exp = extract_bits(value.bits[7], 16, 8);
    if (exp == 0) {
      flag = sign ? 2 : 1;
      copy(result, empty);
    } else {  // число переполнено но есть степень
      big_decimal temp = {0};
      do {
        div_BIGdecimal(value, 10, &temp);
        exp--;
        setEXP(&value, exp);
        if (overflowDecimal(temp) == 0) {
          copy_BIG(&value, temp);
          flag = 0;
        } else if (exp == 0) {
          flag = 1;
          break;
        }
      } while (exp > 0);
      if (flag == 0) flag = convertBigToDecimal(value, result);
    }
  }
  return flag;
}

int get_bit(int num, int n) {  // получение бита в заданной позиции начиная с 0
  int result = (num & 1 << n) != 0 ? 1 : 0;
  return result;
}

void set_bit(int *num, int position, int value) {
  if (value)
    *num |= 1 << position;
  else
    *num &= ~(1 << position);
}

int extract_bits(int num, int start,
                 int n) {  // выделение n битов с заданной позиции
  // Создаем маску с n единицами, начиная с позиции start
  int mask = ~(0b11111111111111111111111111111111 << n) << start;

  // Выполняем побитовое И между числом и маской
  int result = (num & mask) >> start;

  // Возвращаем результат
  return result;
}

void setexp(s21_decimal *value, int exp) {
  int sign = get_bit(value->bits[3], 31);
  value->bits[3] = exp << 16;
  set_bit(&value->bits[3], 31, sign);
}