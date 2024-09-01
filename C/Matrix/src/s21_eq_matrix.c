#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = SUCCESS;
  if (!s21_correct_matrix(A) || !s21_correct_matrix(B) || B->rows != A->rows ||
      B->columns != A->columns) {
    err = FAILURE;
  }

  if (err) {
    for (int i = 0; i < A->rows; i++) {
      if (!err) break;
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          err = FAILURE;
          break;
        }
      }
    }
  }
  return err;
}