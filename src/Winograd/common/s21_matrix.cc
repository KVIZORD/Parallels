#include "s21_matrix.h"


namespace s21 {
	size_t Matrix::GetRows() {
		return rows_;
	}

	size_t Matrix::GetColumns() {
		return cols_;
	}

	Matrix::MatrixType Matrix::GetData() {
		return data_;
	}

	void Matrix::Print() {
		for (size_t i = 0; i < rows_; i++) {
			for (size_t j = 0; j < cols_; j++) {
				std::cout << data_[i][j] << " ";
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
		if (cols_ != other.rows_) throw std::exception("Matrices are not compatible");
		Matrix result(rows_, other.cols_);
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < other.cols_; j++) {
				double sum = 0;
				for (int k = 0; k < cols_; k++) {
					sum += data_[i][k] * other.data_[k][j];
				}
				result.data_[i][j] = sum;
			}
		}		
		return result;		
	}
	Matrix& Matrix::operator=(const Matrix& other) {
		if (this == &other) return *this;
		rows_ = other.rows_;
		cols_ = other.cols_;
		data_ = other.data_;
		return *this;
	}
	void Matrix::SetValue(size_t row, size_t col, double value)	{
		data_[row][col] = value;
	}
}
