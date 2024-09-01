#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool flag = false;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    flag = true;
    for (int i = 0; i < rows_; i++) {
      if (!flag) break;
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          flag = false;
          break;
        }
      }
    }
  }
  return flag;
}