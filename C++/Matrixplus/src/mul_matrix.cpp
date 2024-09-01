#include "s21_matrix_oop.h"

void S21Matrix::MulMatrix(const S21Matrix& other) {
  try {
    if (cols_ != other.rows_) throw invalid_argument("Error calcilating!!");
    S21Matrix temp(rows_, other.cols_);
    // copy_matrix(temp);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        temp.matrix_[i][j] = mul_help(other, i, j);
      }
    }
    set_matrix(other.rows_, cols_);
    move_matrix(temp);
  } catch (const invalid_argument& error) {
    cout << "Exception: " << error.what() << endl;
    throw;
  }
}