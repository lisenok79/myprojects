#include "s21_matrix.h"

void s21_print_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("%f ", A->matrix[i][j]);
    }
    printf("\n");
  }
}

int s21_correct_matrix(matrix_t *A) {
  int err = 1;
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1) {
    err = 0;
  }
  return err;
}

double s21_mult_help(matrix_t *A, matrix_t *B, int i, int j) {
  double res = 0;
  for (int k = 0; k < A->columns; k++) {
    res += A->matrix[i][k] * B->matrix[k][j];
  }
  return res;
}

void s21_cut_matrix(int i, int j, matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  int x = 0;
  int y = 0;
  for (int a = 0; a < A->rows; a++) {
    if (i == a) continue;
    x = 0;
    for (int b = 0; b < A->columns; b++) {
      if (j == b) continue;
      result->matrix[y][x] = A->matrix[a][b];
      x++;
    }
    y++;
  }
}

void s21_det_nn(matrix_t *A, double *result) {
  matrix_t temp = {0};
  int i = 0;
  double res = 0;
  double tmp = 0;
  if (A->columns == 1)
    res = A->matrix[0][0];
  else if (A->columns == 2)
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else {
    for (int j = 0; j < A->rows; j++) {
      s21_remove_matrix(&temp);
      tmp = 0;
      s21_cut_matrix(i, j, A, &temp);
      s21_det_nn(&temp, &tmp);
      res += tmp * pow(-1, i + j) * A->matrix[i][j];
      s21_remove_matrix(&temp);
    }
  }
  s21_remove_matrix(&temp);
  *result = res;
}

void s21_dop(matrix_t *A, matrix_t *result) {
  matrix_t temp = {0};
  double tmp = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      tmp = 0;
      s21_cut_matrix(i, j, A, &temp);
      s21_determinant(&temp, &tmp);
      result->matrix[i][j] = tmp * pow(-1, i + j);
      s21_remove_matrix(&temp);
    }
    s21_remove_matrix(&temp);
  }
  s21_remove_matrix(&temp);
}