#include "s21_matrix_oop.h"

// Доступ к приватным полям класса
int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  try {
    if (rows <= 0) throw string{"Incorrect rows!"};
    // rows_ = rows;
    set_matrix(rows, cols_);
  } catch (string error) {
    cerr << error << endl;
    throw;
  }
}

void S21Matrix::SetCols(int cols) {
  try {
    if (cols <= 0) throw string{"Incorrect rows!"};
    // rows_ = rows;
    set_matrix(rows_, cols);
  } catch (string error) {
    cerr << error << endl;
    throw;
  }
}

// Увеличить/уменьшить матрицу
void S21Matrix::set_matrix(int rows, int cols) {
  S21Matrix new_matrix(rows, cols);
  for (int i = 0; i < min(rows_, rows); i++) {
    for (int j = 0; j < min(cols_, cols); j++) {
      new_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  transfer_matrix(new_matrix);
}
// ====================================================

// Печать матрицы
void S21Matrix::print_matrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      cout << matrix_[i][j] << ' ';
    }
    cout << endl;
  }
}

// Заполнение матрицы
void S21Matrix::fill_matrix() {
  int a = 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = a;
      a++;
    }
  }
  matrix_[1][1] = a - 1;
}

// Выделение памяти под матрицу
void S21Matrix::create() {
  try {
    if (rows_ < 1 || cols_ < 1) throw string{"Incorrect rows or cols!"};
    matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]();
    }
  } catch (string error) {
    cerr << error << endl;
    matrix_ = nullptr;
    throw;
  }
}

// Скопировать текущую матрицу в новую
void S21Matrix::copy_matrix(S21Matrix& new_matrix) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      new_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  new_matrix.rows_ = rows_;
  new_matrix.cols_ = cols_;
}

// Скопировать матрицу в текущую
void S21Matrix::matrix_copy(const S21Matrix& other) {
  set_matrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Перенести матрицу в текущую
void S21Matrix::move_matrix(S21Matrix& other) {
  matrix_copy(other);
  transfer_matrix(other);
}

// Перенести указатель и все данные из матрицы в текущую
void S21Matrix::transfer_matrix(S21Matrix& other) {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

// Умножение матриц хелпер
double S21Matrix::mul_help(const S21Matrix& B, int i, int j) {
  double res = 0;
  for (int k = 0; k < cols_; k++) {
    res += matrix_[i][k] * B.matrix_[k][j];
  }
  return res;
}

// Вырезать матрицу
void S21Matrix::cut_matrix(int i, int j, S21Matrix& temp) {
  // S21Matrix temp(rows_ - 1, cols_ - 1);
  int x = 0;
  int y = 0;
  for (int a = 0; a < rows_; a++) {
    if (i == a) continue;
    x = 0;
    for (int b = 0; b < cols_; b++) {
      if (j == b) continue;
      temp.matrix_[y][x] = matrix_[a][b];
      x++;
    }
    y++;
  }
  // set_matrix(rows_ - 1, cols_ - 1);
  // copy(temp);
  // return temp;
}

// Нахождение детерминанта
void S21Matrix::det_nn(double* result) {
  // copy_matrix(temp);
  int i = 0;
  double res = 0;
  double tmp = 0;
  if (cols_ == 1)
    res = matrix_[0][0];
  else if (cols_ == 2)
    res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else {
    for (int j = 0; j < rows_; j++) {
      S21Matrix temp(rows_ - 1, cols_ - 1);
      tmp = 0;
      cut_matrix(i, j, temp);
      temp.det_nn(&tmp);
      res += tmp * pow(-1, i + j) * matrix_[i][j];
    }
  }
  *result = res;
}

// Нахождение алгебраических дополнений
void S21Matrix::dop(S21Matrix& result) {
  // copy_matrix(temp);
  double tmp = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix temp(rows_ - 1, cols_ - 1);
      tmp = 0;
      cut_matrix(i, j, temp);
      tmp = temp.Determinant();
      result.matrix_[i][j] = tmp * pow(-1, i + j);
    }
  }
}