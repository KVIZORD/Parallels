#include "s21_winograd.h"

namespace s21 {

	Winograd::Winograd(const WinogradData& data) {
		data_ = data;
		a_rows_ = data_.a.GetRows();
		a_cols_ = data_.a.GetColumns();
		b_rows_ = data_.b.GetRows();
		b_cols_ = data_.b.GetColumns();
	}

	WinogradData Winograd::GetData() {
		return data_;
	}

	void Winograd::SetData(const WinogradData& data) {
		data_ = data;
	}

	Matrix Winograd::MulMatrix() {
		if (a_cols_ != b_rows_) throw std::exception("Matrices are not compatible");
		Matrix result(a_rows_, b_cols_);
		for (int i = 0; i < a_rows_; i++) {
			for (int j = 0; j < b_cols_; j++) {
				double sum = 0;
				for (int k = 0; k < a_cols_; k++) {
					sum += data_.a(i, k) * data_.b(k, j);
				}
				result(i, j) = sum;
			}
		}
		return result;
	}

	Winograd::Vector  Winograd::RowFactor() {
		Vector rowFactor(a_rows_);
		size_t d = a_cols_ / 2;
		for (size_t i = 0; i < a_rows_; ++i) {
			rowFactor[i] = data_.a(i, 0) * data_.a(i, 1);
			for (size_t j = 1; j < d; ++j) {
				rowFactor[i] += data_.a(i, 2 * j) * data_.a(i, 2 * j + 1);
			}
		}
		return rowFactor;
	}

	Winograd::Vector Winograd::ColumnFactor() {
		Vector columnFactor(b_cols_);
		size_t d = a_cols_ / 2;
		for (size_t i = 0; i < b_cols_; ++i) {
			columnFactor[i] = data_.b(0, i) * data_.b(1, i);
			for (size_t j = 1; j < d; ++j) {
				columnFactor[i] += data_.b(2 * j, i) * data_.b(2 * j + 1, i);
			}
		}
		return columnFactor;
	}

	void Winograd::CalculateMatrixWinograd(Matrix& result) {
		size_t d = a_cols_ / 2;
		for (size_t i = 0; i < a_rows_; ++i) {
			for (size_t j = 0; j < b_cols_; ++j) {
				for (size_t k = 0; k < d; ++k) {
					w_mutex.lock();
					result(i, j) += (data_.a(i, 2 * k) + data_.b(2 * k + 1, j)) * (data_.a(i, 2 * k + 1) + data_.b(2 * k, j));
					w_mutex.unlock();
				}
			}
		}
	}

	void Winograd::AddFactors(Vector& rowFactor, Vector& columnFactor, Matrix& result) {
		for (size_t i = 0; i < a_rows_; ++i) {
			for (size_t j = 0; j < b_cols_; ++j) {
				w_mutex.lock();
				result(i, j) += -rowFactor[i] - columnFactor[j];
				w_mutex.unlock();
			}
		}
	}

	void Winograd::AddElementsOddMatrix(Matrix& result) {
		for (size_t i = 0; i < a_rows_; ++i) {
			for (size_t j = 0; j < b_cols_; ++j) {
				w_mutex.lock();
				result(i, j) += data_.a(i, a_cols_ - 1) * data_.b(a_cols_ - 1, j);
				w_mutex.unlock();
			}
		}
	}

	Matrix Winograd::MulMatrixWinograd() {
		if (a_cols_ != b_rows_) {
			throw std::exception("Matrices are not compatible");
		}
		Vector rowFactor(RowFactor());
		Vector columnFactor(ColumnFactor());
		Matrix result(a_rows_, b_cols_);
		CalculateMatrixWinograd(result);
		AddFactors(rowFactor, columnFactor, result);
		if (a_cols_ % 2) {
			AddElementsOddMatrix(result);
		}
		return result;
	}

	Matrix Winograd::MulMatrixConveyorWinograd() {
		if (a_cols_ != b_rows_) {
			throw std::exception("Matrices are not compatible");
		}
		Vector rowFactor;
		Vector columnFactor;
		Matrix result(a_rows_, b_cols_);
		std::condition_variable cv;
		std::mutex m_factors;
		bool unblock = false;

		std::thread t1([&]() {
			CalculateMatrixWinograd(result);
			}
		);
		std::thread t2([&]() {
			if (a_cols_ % 2) {
				AddElementsOddMatrix(result);
			}
			}
		);

		std::thread t3([&]() {
			std::unique_lock<std::mutex> ul(m_factors);
			rowFactor = RowFactor(); 
			columnFactor = ColumnFactor(); 
			unblock = true;
			cv.notify_one();
			}
		);

		std::thread t4([&]() {
			std::unique_lock<std::mutex> ul(m_factors);
			cv.wait(ul, [&]{return unblock; });
			AddFactors(rowFactor, columnFactor, result);
			}
		);
				
		t1.join();
		t2.join();
		t3.join();
		t4.join();

		return result;
	}


}
