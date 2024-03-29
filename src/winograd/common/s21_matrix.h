#ifndef PARALLELS_SOURCE_WINOGRAD_COMMON_S21_MATRIX_H_
#define PARALLELS_SOURCE_WINOGRAD_COMMON_S21_MATRIX_H_

#include <exception>
#include <iomanip>
#include <iostream>
#include <vector>

namespace s21 {
class Matrix {
  using MatrixType = std::vector<std::vector<double>>;

 public:
  Matrix() = default;
  Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    std::vector<double> r(cols, 0);
    data_ = MatrixType(rows, r);
  }
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);

  size_t GetRows() const;
  size_t GetColumns() const;
  MatrixType GetData() const;
  void Print() const;
  void RandomMatrix();
  void FillFromConsoleMatrix();
  Matrix MulMatrix(const Matrix& other);

  Matrix& operator=(const Matrix& other);
  double& operator()(size_t row, size_t col);

 private:
  size_t rows_{};
  size_t cols_{};
  MatrixType data_{};
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_WINOGRAD_COMMON_S21_MATRIX_H_