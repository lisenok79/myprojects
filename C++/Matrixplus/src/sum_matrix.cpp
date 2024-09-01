#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& other) {
  try {
    if (rows_ != other.rows_ || cols_ != other.cols_)
      throw invalid_argument("Different dimensions of the matrices!");
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } catch (const invalid_argument& error) {
    cout << "Exception: " << error.what() << endl;
    throw;
  }
}