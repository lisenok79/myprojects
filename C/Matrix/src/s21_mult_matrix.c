#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!s21_correct_matrix(A) || !s21_correct_matrix(B)) {
    err = 1;
  } else if (A->columns != B->rows) {
    err = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = s21_mult_help(A, B, i, j);
      }
    }
  }
  return err;
}