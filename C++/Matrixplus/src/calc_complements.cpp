#include "s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  try {
    if (rows_ != cols_) throw string{"Matrix is not square!"};
    if (rows_ == 1)
      result.matrix_[0][0] = 1;
    else
      dop(result);
  } catch (string error) {
    cout << error << endl;
    throw;
  }
  return result;
}