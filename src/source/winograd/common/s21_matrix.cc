#include "s21_matrix.h"

namespace s21 {
size_t Matrix::GetRows() const { return rows_; }

size_t Matrix::GetColumns() const { return cols_; }

Matrix::MatrixType Matrix::GetData() const { return data_; }

void Matrix::Print() const {
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      std::cout << std::setw(5) << data_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Matrix::RandomMatrix() {
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      data_[i][j] = rand() % 10;
    }
  }
}

void Matrix::FillFromConsoleMatrix() {
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      std::cout << "Input matrix element: ";
      std::cin >> data_[i][j];
    }
  }
}

Matrix Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Matrices are not compatible");
  }
  Matrix result(rows_, other.cols_);
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < other.cols_; j++) {
      double sum = 0;
      for (size_t k = 0; k < cols_; k++) {
        sum += data_[i][k] * other.data_[k][j];
      }
      result.data_[i][j] = sum;
    }
  }
  return result;
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

Matrix::Matrix(Matrix&& other)
    : rows_(std::move(other.rows_)),
      cols_(std::move(other.cols_)),
      data_(std::move(other.data_)) {}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) return *this;
  rows_ = other.rows_;
  cols_ = other.cols_;
  data_ = other.data_;
  return *this;
}

double& Matrix::operator()(size_t row, size_t col) {
  if (row >= rows_ || col >= cols_) throw std::out_of_range("Incorrect index");
  return data_[row][col];
}
}  // namespace s21
