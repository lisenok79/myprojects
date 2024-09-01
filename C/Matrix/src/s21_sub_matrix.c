#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!s21_correct_matrix(A) || !s21_correct_matrix(B)) {
    err = 1;
  } else if (B->rows != A->rows || B->columns != A->columns) {
    err = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return err;
}