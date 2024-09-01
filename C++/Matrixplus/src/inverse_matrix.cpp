#include "s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result(rows_, cols_);
  copy_matrix(result);
  try {
    double det = Determinant();
    if (det == 0) throw string{"Определитель матрицы равен 0!"};
    auto res = CalcComplements().Transpose();
    result = res;
    result.MulNumber(1 / det);
  } catch (string error) {
    cout << error << endl;
    throw;
  }
  return result;
}