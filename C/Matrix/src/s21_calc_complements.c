#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (!s21_correct_matrix(A)) {
    err = 1;
  } else if (A->columns != A->rows) {
    err = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1)
      result->matrix[0][0] = A->matrix[0][0];
    else
      s21_dop(A, result);
  }
  return err;
}