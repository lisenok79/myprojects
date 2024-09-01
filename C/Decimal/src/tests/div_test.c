#include "tests.h"

START_TEST(s21_div_1) {
  s21_decimal src1, src2, result, origin;
  // 30064771176
  // 3
  // 10021590392
  src1.bits[0] = 0b00000000000000000000000001101000;
  src1.bits[1] = 0b00000000000000000000000000000111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;

  origin.bits[0] = 0b01010101010101010101010101111000;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal src1, src2, result;
  int a = 32768;
  int b = -2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -16384;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_decimal_to_int(result, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal src1, src2, result;
  int a = 32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 16384;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_decimal_to_int(result, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal src1, src2, result, origin;
  // -30064771176
  // 2
  // 10021590392
  src1.bits[0] = 0b00000000000000000000000001101000;
  src1.bits[1] = 0b00000000000000000000000000000111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;

  origin.bits[0] = 0b10000000000000000000000000110100;
  origin.bits[1] = 0b00000000000000000000000000000011;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal src1, src2, result, origin;
  // 0
  // 0.015
  // 0
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000001111;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal src1, src2, result, origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b00000000000000000000000000000000;

  origin.bits[0] = 1;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_7) {
  s21_decimal src1, src2, result, origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b00000000000000000000000000000000;

  origin.bits[0] = 1;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal src1, src2, result, origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b10000000000000000000000000000000;

  origin.bits[0] = 1;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal src1, src2, result, origin;
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b11111111111111111111111111111111;
  src2.bits[1] = 0b11111111111111111111111111111111;
  src2.bits[2] = 0b11111111111111111111111111111111;
  src2.bits[3] = 0b10000000000000000000000000000000;

  origin.bits[0] = 1;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal src1, src2, result, origin;
  src1.bits[0] = 300000;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;

  src2.bits[0] = 30;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;

  origin.bits[0] = 10000;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

// START_TEST(s21_div_11) {
//   s21_decimal src1, src2, result, origin;
//   src1.bits[0] = 30;
//   src1.bits[1] = 0;
//   src1.bits[2] = 0;
//   src1.bits[3] = 0;

//   src2.bits[0] = 100;
//   src2.bits[1] = 0;
//   src2.bits[2] = 0;
//   src2.bits[3] = 0;

//   origin.bits[0] = 3;
//   origin.bits[1] = 0;
//   origin.bits[2] = 0;
//   origin.bits[3] = 0b00000000000000010000000000000000;
//   int check = s21_div(src1, src2, &result);
//   int check_origin = 0;
//   ck_assert_int_eq(check, check_origin);
//   ck_assert_int_eq(result.bits[3], origin.bits[3]);
//   ck_assert_int_eq(result.bits[2], origin.bits[2]);
//   ck_assert_int_eq(result.bits[1], origin.bits[1]);
//   ck_assert_int_eq(result.bits[0], origin.bits[0]);
// }
// END_TEST

START_TEST(s21_div_12) {
  s21_decimal src1, src2, result, origin;
  // 79 228 162 514 264 337 593 543 950 335
  // 79 228 162 514 264 337 593 543.950 335
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0;

  src2.bits[0] = 1000000;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;

  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b11111111111111111111111111111111;
  origin.bits[3] = 0b00000000000001100000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal src1, src2, result, origin;
  // 8/5 = 1.6
  src1.bits[0] = 8;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0;

  src2.bits[0] = 5;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0;

  origin.bits[0] = 16;
  origin.bits[1] = 0;
  origin.bits[2] = 0;
  origin.bits[3] = 0b00000000000000010000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

// START_TEST(s21_div_14) {
//   s21_decimal src1, src2, result, origin;
//   // 38/7 = 5.428 571 428 571 428 571 428 571 428 6
//   src1.bits[0] = 38;
//   src1.bits[1] = 0;
//   src1.bits[2] = 0;
//   src1.bits[3] = 0;

//   src2.bits[0] = 7;
//   src2.bits[1] = 0;
//   src2.bits[2] = 0;
//   src2.bits[3] = 0;

//   origin.bits[0] = 0b00001101101101101101101101101110;
//   origin.bits[1] = 0b00101100110010001110100001011000;
//   origin.bits[2] = 0b10101111011010000001011100100100;
//   origin.bits[3] = 0b00000000000111000000000000000000;
//   int check = s21_div(src1, src2, &result);
//   int check_origin = 0;
//   ck_assert_int_eq(check, check_origin);
//   ck_assert_int_eq(result.bits[3], origin.bits[3]);
//   ck_assert_int_eq(result.bits[2], origin.bits[2]);
//   ck_assert_int_eq(result.bits[1], origin.bits[1]);
//   ck_assert_int_eq(result.bits[0], origin.bits[0]);
// }
// END_TEST

START_TEST(s21_div_15) {
  s21_decimal src1, src2, result;
  src1.bits[0] = 0x0006BFD0;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000028;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check_origin, check);
  ck_assert_int_eq(result.bits[3], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[0], 0x00002B32);
}
END_TEST

START_TEST(s21_div_null_16) {
  s21_decimal dec1 = {{1110, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};

  s21_decimal res1;
  int res = s21_div(dec1, dec2, &res1);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_div_17) {
  s21_decimal src1, src2, result;
  // 79 228 162 514 264 337 593 543 950 335
  // 79 228 162 514 264 337 593 543.950 335
  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000100;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b0000000000000001000000000000000;

  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check_origin, check);
}
END_TEST

Suite *div_lib_suite() {
  Suite *suite = suite_create("Cast");
  TCase *tc1_div = tcase_create("Cast");
  tcase_add_test(tc1_div, s21_div_1);
  tcase_add_test(tc1_div, s21_div_2);
  tcase_add_test(tc1_div, s21_div_3);
  tcase_add_test(tc1_div, s21_div_4);
  tcase_add_test(tc1_div, s21_div_5);
  tcase_add_test(tc1_div, s21_div_6);
  tcase_add_test(tc1_div, s21_div_7);
  tcase_add_test(tc1_div, s21_div_8);
  tcase_add_test(tc1_div, s21_div_9);
  tcase_add_test(tc1_div, s21_div_10);
  tcase_add_test(tc1_div, s21_div_12);
  tcase_add_test(tc1_div, s21_div_13);
  // tcase_add_test(tc1_div, s21_div_14);
  tcase_add_test(tc1_div, s21_div_15);
  tcase_add_test(tc1_div, s21_div_null_16);
  tcase_add_test(tc1_div, s21_div_17);
  suite_add_tcase(suite, tc1_div);

  return suite;
}