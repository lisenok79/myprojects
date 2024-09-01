#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int err = 0;
  if (!s21_correct_matrix(A)) {
    err = 1;
  } else if (A->columns != A->rows) {
    err = 2;
  } else {
    s21_det_nn(A, result);
  }
  return err;
}