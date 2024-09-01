#include "s21_matrix_oop.h"

double S21Matrix::Determinant() {
  double result = 0;
  try {
    if (rows_ != cols_) throw string{"Matrix is not square!"};
    det_nn(&result);
  } catch (string error) {
    cout << error << endl;
    throw;
  }
  return result;
}