#include "s21_matrix_oop.h"

using namespace std;

// конструкторы и деконструктор
S21Matrix::S21Matrix() : rows_(2), cols_(2) { s21_create_matrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  s21_create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int y = 0; y < cols_; y++) {
      matrix_[i][y] = other.matrix_[i][y];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) : S21Matrix(other) {
  other.~S21Matrix();
}

void S21Matrix::s21_create_matrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::setRows(int rows) {
  S21Matrix newMatrix(rows, cols_);
  for (int i = 0; i < rows; i++) {
    for (int y = 0; y < cols_; y++) {
      if (i < rows_) {
        newMatrix.matrix_[i][y] = matrix_[i][y];
      } else {
        newMatrix.matrix_[i][y] = 0;
      }
    }
  }
  *this = newMatrix;
}

void S21Matrix::setCols(int cols) {
  S21Matrix newMatrix(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int y = 0; y < cols; y++) {
      if (y < cols_) {
        newMatrix.matrix_[i][y] = matrix_[i][y];
      } else {
        newMatrix.matrix_[i][y] = 0;
      }
    }
  }
  *this = newMatrix;
}

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

// операторы переопределения

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    this->~S21Matrix();
    cols_ = other.cols_;
    rows_ = other.rows_;
    s21_create_matrix();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 1 || row > rows_ || col < 1 || col > cols_) {
    throw out_of_range("Не корректный ввод");
  }
  return matrix_[row - 1][col - 1];
}

// фунции с матрицами

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool equal = false;
  equal = (rows_ == other.rows_ && cols_ == other.cols_) ? true : false;
  for (int i = 0; i < rows_; i++) {
    for (int y = 0; y < cols_ && equal == true; y++) {
      equal &=
          (fabs(matrix_[i][y] - other.matrix_[i][y]) < 1e-7) ? true : false;
    }
  }
  return equal;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int y = 0; y < cols_; y++) {
        matrix_[i][y] += other.matrix_[i][y];
      }
    }
  } else {
    throw out_of_range("матрицы разных размеров");
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int y = 0; y < cols_; y++) {
        matrix_[i][y] -= other.matrix_[i][y];
      }
    }
  } else {
    throw out_of_range("матрицы разных размеров");
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int y = 0; y < cols_; y++) {
      matrix_[i][y] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw out_of_range(
        "число столбцов первой матрицы не равно числу строк второй матрицы");
  }

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0.0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transpose(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int y = 0; y < cols_; y++) {
      transpose.matrix_[y][i] = matrix_[i][y];
    }
  }
  return transpose;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw out_of_range("Матрица не квадратная");
  }
  double det = 1.0;
  S21Matrix temp(*this);
  for (int i = 0; i < rows_; i++) {
    if (temp.matrix_[i][i] == 0) {
      bool found_nonzero = false;
      for (int y = i + 1; y < rows_; y++) {
        if (temp.matrix_[y][i] != 0) {
          found_nonzero = true;
          std::swap_ranges(temp.matrix_[i], temp.matrix_[i] + cols_,
                           temp.matrix_[y]);
          det = -det;
          break;
        }
      }
      if (!found_nonzero) {
        return 0;
      }
    }
    det *= temp.matrix_[i][i];
    for (int y = i + 1; y < rows_; y++) {
      double factor = temp.matrix_[y][i] / temp.matrix_[i][i];
      for (int k = i + 1; k < rows_; k++) {
        temp.matrix_[y][k] -= factor * temp.matrix_[i][k];
      }
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw out_of_range("Матрица не квадратная");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(i, j);
      double determinant = minor.Determinant();
      double algebraic_complement = pow(-1, i + j) * determinant;
      result.matrix_[i][j] = algebraic_complement;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (this->Determinant() == 0) {
    throw out_of_range("Определитель матрицы равен 0");
  }
  double determinant = 1 / Determinant();
  S21Matrix InverseMatrix = CalcComplements().Transpose();
  InverseMatrix.MulNumber(determinant);
  return InverseMatrix;
}

// доп функции
S21Matrix S21Matrix::GetMinor(int row, int col) const {
  if (rows_ != cols_) {
    throw out_of_range("Матрица не квадратная");
  }
  S21Matrix result(rows_ - 1, cols_ - 1);
  int row_offset = 0;
  for (int i = 0; i < rows_ - 1; i++) {
    if (i == row) {
      row_offset = 1;
    }
    int col_offset = 0;
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == col) {
        col_offset = 1;
      }
      result.matrix_[i][j] = matrix_[i + row_offset][j + col_offset];
    }
  }
  return result;
}