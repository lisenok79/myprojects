#include "s21_decimal.h"

int s21_get_bit(int value, int position) { return value >> position & 1; }

int s21_get_bit_decimal(s21_decimal value, int position) {
  int res = -1;
  if (position >= 0 && position < 32)
    res = s21_get_bit(value.bits[0], position);
  else if (position >= 32 && position < 64)
    res = s21_get_bit(value.bits[1], position - 32);
  else if (position >= 64 && position < 96)
    res = s21_get_bit(value.bits[2], position - 64);
  // else if (position >= 96 && position < 128) res = s21_get_bit(value.bits[3],
  // position - 96);
  return res;
}

int s21_set_bit(int *value, int bit, int position) {
  int current = s21_get_bit(*value, position);
  int mask = 1 << position;
  if (current == 0 && bit == 1)
    *value = *value | mask;
  else
    *value = *value & ~mask;
  return *value;
}

void s21_set_bit_decimal(s21_decimal *value, int bit, int position) {
  if (position >= 0 && position < 32)
    s21_set_bit(&value->bits[0], bit, position);
  else if (position >= 32 && position < 64)
    s21_set_bit(&value->bits[1], bit, position - 32);
  else if (position >= 64 && position < 96)
    s21_set_bit(&value->bits[2], bit, position - 64);
  else if (position >= 96 && position < 128)
    s21_set_bit(&value->bits[3], bit, position - 96);
}

int s21_get_pow(s21_decimal value) {
  int penis = 0b11111111;
  int mask = penis << 16;
  int res = (value.bits[3] & mask) >> 16;
  return res;
}

int get_exp(float *value) {
  return ((*((int *)value) & ~(1 << 31)) >> 23) - 127;
}

s21_decimal *set_scale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    value->bits[3] &= ~(0b11111111 << 16);
    value->bits[3] |= scale << 16;
  }
  return value;
}
