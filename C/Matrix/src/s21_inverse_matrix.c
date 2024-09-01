#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  matrix_t calc_temp = {0};
  matrix_t trans_temp = {0};
  int err = 0;
  double det = 0;
  s21_determinant(A, &det);
  if (!s21_correct_matrix(A)) {
    err = 1;
  } else if (A->columns != A->rows || det == 0) {
    err = 2;
  } else {
    s21_calc_complements(A, &calc_temp);
    s21_transpose(&calc_temp, &trans_temp);
    s21_mult_number(&trans_temp, 1 / det, result);
  }
  s21_remove_matrix(&calc_temp);
  s21_remove_matrix(&trans_temp);
  return err;
}