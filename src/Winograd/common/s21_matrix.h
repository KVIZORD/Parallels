#ifndef PARALLELS_WINOGRAD_COMMON_MATRIX_H
#define PARALLELS_WINOGRAD_COMMON_MATRIX_H

#include <vector>
#include <iostream>

namespace s21 {
class Matrix
{
	using MatrixType = std::vector <std::vector<double>>;

public:
	Matrix() = default;
	Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
		std::vector<double> r(cols, 0);
		data_ = MatrixType(rows, r);
	}
	size_t GetRows();
	size_t GetColumns();
	MatrixType GetData();
	void Print();
	void RandomMatrix();
	void FillFromConsoleMatrix();
	Matrix MulMatrix(const Matrix& other);
	Matrix& operator= (const Matrix& other);
	void SetValue(size_t row, size_t col, double value);

private:
	size_t rows_{};
	size_t cols_{};
	MatrixType data_{};
};

} // namespace s21

#endif  // PARALLELS_WINOGRAD_COMMON_MATRIX_H