#include <cmath>
#include <iostream>

using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // Task
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Operators
  S21Matrix operator+(S21Matrix& other);
  S21Matrix operator-(S21Matrix& other);
  S21Matrix operator*(S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  bool operator==(S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  double& operator()(int i, int j);

  // helper
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  void set_matrix(int rows, int cols);
  void transfer_matrix(S21Matrix& other);
  void move_matrix(S21Matrix& other);
  void matrix_copy(const S21Matrix& other);
  void copy_matrix(S21Matrix& new_matrix);
  void print_matrix();
  void fill_matrix();
  void create();
  double mul_help(const S21Matrix& B, int i, int j);
  void det_nn(double* result);
  void cut_matrix(int i, int j, S21Matrix& temp);
  void dop(S21Matrix& result);
};