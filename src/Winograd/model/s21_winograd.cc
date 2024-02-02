#include "s21_winograd.h"

namespace s21 {

	Matrix Winograd::MulMatrix() {
		if (data_.a.GetColumns() != data_.b.GetRows()) throw std::exception("Matrices are not compatible");
		Matrix result(data_.a.GetRows(), data_.b.GetColumns());
		for (int i = 0; i < data_.a.GetRows(); i++) {
			for (int j = 0; j < data_.b.GetColumns(); j++) {
				double sum = 0;
				for (int k = 0; k < data_.a.GetColumns(); k++) {
					sum += data_.a(i, k) * data_.b(k, j);
				}
				result(i, j) = sum;
			}
		}
		return result;
	}

	Winograd::Vector  Winograd::RowFactor() {
		Vector rowFactor;
		size_t d = data_.a.GetColumns() / 2;
		for (size_t i = 0; i < data_.a.GetRows(); ++i) {
			rowFactor.push_back(data_.a(i, 0) * data_.a(i, 1));
			for (size_t j = 1; j < d; ++j) {
				rowFactor[i] += data_.a(i, 2 * j) * data_.a(i, 2 * j + 1);
			}
		}
		return rowFactor;
	}

	Winograd::Vector Winograd::ColumnFactor() {
		Vector columnFactor;
		size_t d = data_.a.GetColumns() / 2;
		for (size_t i = 0; i < data_.b.GetColumns(); ++i) {
			columnFactor.push_back(data_.b(0, i) * data_.b(1, i));
			for (size_t j = 1; j < d; ++j) {
				columnFactor[i] += data_.b(2 * j, i) * data_.b(2 * j + 1, i);
			}
		}
		return columnFactor;
	}

	void Winograd::CalculateMatrixWinograd(Winograd::Vector rowFactor, Winograd::Vector columnFactor, Matrix& result) {
		size_t d = data_.a.GetColumns() / 2;
		for (size_t i = 0; i < data_.a.GetRows(); ++i) {
			for (size_t j = 0; j < data_.b.GetColumns(); ++j) {
				{
					std::unique_lock<std::mutex> lock(w_mutex);
					result(i, j) = -rowFactor[i] - columnFactor[j];
					for (size_t k = 0; k < d; ++k) {
						result(i, j) += (data_.a(i, 2 * k) + data_.b(2 * k + 1, j)) * (data_.a(i, 2 * k + 1) + data_.b(2 * k, j));
					}
				}
			}
		}
	}

	void Winograd::AddElementsOddMatrix(Matrix& result) {
		for (size_t i = 0; i < data_.a.GetRows(); ++i) {
			for (size_t j = 0; j < data_.b.GetColumns(); ++j) {
				{
					std::unique_lock<std::mutex> lock(w_mutex);
					result(i, j) += data_.a(i, data_.a.GetColumns() - 1) * data_.b(data_.a.GetColumns() - 1, j);
				}
			}
		}
	}

	Matrix Winograd::MulMatrixWinograd() {
		if (data_.a.GetColumns() != data_.b.GetRows()) {
			throw std::exception("Matrices are not compatible");
		}
		Vector rowFactor = RowFactor();
		Vector columnFactor = ColumnFactor();
		Matrix result(data_.a.GetRows(), data_.b.GetColumns());
		CalculateMatrixWinograd(rowFactor, columnFactor, result);
		if (data_.a.GetColumns() % 2) {
			AddElementsOddMatrix(result);
		}
		return result;
	}

	Matrix Winograd::MulMatrixConveyorWinograd() {
		if (data_.a.GetColumns() != data_.b.GetRows()) {
			throw std::exception("Matrices are not compatible");
		}
		Vector rowFactor;
		Vector columnFactor;
		Matrix result(data_.a.GetRows(), data_.b.GetColumns());

		std::thread t1([&]() {
			rowFactor = RowFactor(); }
		);

		std::thread t2([&]() {
			columnFactor = ColumnFactor(); }
		);

		t1.join();
		t2.join();

		std::thread t3([&]() {
			CalculateMatrixWinograd(rowFactor, columnFactor, result);
			}
		);

		std::thread t4([&]() {
			if (data_.a.GetColumns() % 2) {
				AddElementsOddMatrix(result);
			}
			}
		);
		t3.join();
		t4.join();

		return result;
	}

	Winograd::Winograd(const WinogradData& data) {
		data_ = data;
	}

	WinogradData Winograd::GetData() {
		return data_;
	}

	void Winograd::SetData(const WinogradData& data) {
		data_ = data;
	}
}
