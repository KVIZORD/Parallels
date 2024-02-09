#include "s21_winograd.h"

namespace s21 {

	Winograd::Winograd(const WinogradData& data)
		: data_(data),
		a_rows_(data_.a.GetRows()),
		a_cols_(data_.a.GetColumns()),
		b_rows_(data_.b.GetRows()),
		b_cols_(data_.b.GetColumns()) {}

	WinogradData Winograd::GetData() const { return data_; }

	void Winograd::SetData(const WinogradData& data) { data_ = data; }

	Matrix Winograd::MulMatrix() {
		if (a_cols_ != b_rows_)
			throw std::invalid_argument("Matrices are not compatible");
		Matrix result(a_rows_, b_cols_);
		for (size_t i = 0; i < a_rows_; i++) {
			for (size_t j = 0; j < b_cols_; j++) {
				double sum = 0;
				for (size_t k = 0; k < a_cols_; k++) {
					sum += data_.a(i, k) * data_.b(k, j);
				}
				result(i, j) = sum;
			}
		}
		return result;
	}

	Winograd::Vector Winograd::RowFactor() {
		Vector row_factor(a_rows_);
		for (size_t i = 0; i < a_rows_; ++i) {
			row_factor[i] = RowFactorElement(i);
		}
		return row_factor;
	}

	double Winograd::RowFactorElement(size_t i) {
		double result = data_.a(i, 0) * data_.a(i, 1);
		size_t d = a_cols_ / 2;
		for (size_t j = 1; j < d; ++j) {
			result += data_.a(i, 2 * j) * data_.a(i, 2 * j + 1);
		}
		return result;
	}

	Winograd::Vector Winograd::ColumnFactor() {
		Vector column_factor(b_cols_);
		size_t d = a_cols_ / 2;
		for (size_t i = 0; i < b_cols_; ++i) {
			column_factor[i] = ColumnFactorElement(i);
		}
		return column_factor;
	}


	double Winograd::ColumnFactorElement(size_t i) {
		double result = data_.b(0, i) * data_.b(1, i);
		size_t d = a_cols_ / 2;
		for (size_t j = 1; j < d; ++j) {
			result += data_.b(2 * j, i) * data_.b(2 * j + 1, i);
		}
		return result;
	}

	void Winograd::CalculateMatrixWinograd(Matrix& result) {
		size_t d = a_cols_ / 2;
		for (size_t i = 0; i < a_rows_; ++i) {
			for (size_t j = 0; j < b_cols_; ++j) {
				for (size_t k = 0; k < d; ++k) {
					w_mutex.lock();
					result(i, j) += (data_.a(i, 2 * k) + data_.b(2 * k + 1, j)) *
						(data_.a(i, 2 * k + 1) + data_.b(2 * k, j));
					w_mutex.unlock();
				}
			}
		}
	}

	void Winograd::AddFactors(const Vector& row_factor, const Vector& column_factor,
		Matrix& result) {
		for (size_t i = 0; i < a_rows_; ++i) {
			for (size_t j = 0; j < b_cols_; ++j) {
				w_mutex.lock();
				result(i, j) += -row_factor[i] - column_factor[j];
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
			throw std::invalid_argument("Matrices are not compatible");
		}
		Vector row_factor(RowFactor());
		Vector column_factor(ColumnFactor());
		Matrix result(a_rows_, b_cols_);
		CalculateMatrixWinograd(result);
		AddFactors(row_factor, column_factor, result);
		if (a_cols_ % 2) {
			AddElementsOddMatrix(result);
		}
		return result;
	}

	Matrix Winograd::MulMatrixParallelWinograd(size_t threads) {
		std::vector<std::thread> threads_pool;
		threads_pool.reserve(threads);

		Matrix result(a_rows_, b_cols_);
		Vector row_factor(a_rows_);
		Vector column_factor(b_cols_);
		
		size_t index_row_factor = 0;
		size_t index_col_factor = 0;
		size_t index_row_element = 0;
		size_t index_col_element = 0;
		for (size_t a = 0; a < threads; a++) {
			threads_pool.emplace_back(std::thread([&]() {
				size_t i = 0;
				size_t j = 0;
				while (true) {
					{
						std::unique_lock<std::mutex> lock(w_mutex);
						if (!CheckRawFactorIndex(i, index_row_factor)) break;
					}
					row_factor[i] = RowFactorElement(i);
				}
				while (true) {
					{
						std::unique_lock<std::mutex> lock(w_mutex);
						if (!CheckColumnFactorIndex(i, index_col_factor)) break;
					}
					column_factor[i] = ColumnFactorElement(i);
				}

				while (true) {
					{
						std::unique_lock<std::mutex> lock(w_mutex);
						if (!CheckMatrixIndex(i, j, index_row_element, index_col_element)) break;
					}
					result(i, j) = CalculateMatrixElement(i, j, row_factor, column_factor);
				}
				}));
		}
		for (auto& thread : threads_pool) {
			if (thread.joinable())
				thread.join();
		}
		return result;
	}

	double Winograd::CalculateMatrixElement(size_t i, size_t j, Vector& row_factor, Vector& column_factor) {
		size_t d = a_cols_ / 2;		
		double result = -row_factor[i] - column_factor[j];
		for (size_t k = 0; k < d; ++k) {
			result += (data_.a(i, 2 * k) + data_.b(2 * k + 1, j)) *
				(data_.a(i, 2 * k + 1) + data_.b(2 * k, j));
		}
		if (a_cols_ % 2) {
			result += data_.a(i, a_cols_ - 1) * data_.b(a_cols_ - 1, j);
		}
		return result;
	}


	bool Winograd::CheckMatrixIndex(size_t& i, size_t& j, size_t& row, size_t& col) const{
		if (row >= a_rows_) return false;
		i = row;
		j = col;
		++col;
		if (col >= b_cols_) {
			++row;
			col = 0;
		}
		return true;
	}

	bool Winograd::CheckRawFactorIndex(size_t& i, size_t& row) const {
		i = row;
		++row;
		if (row > a_rows_) return false;
		return true;
	}

	bool Winograd::CheckColumnFactorIndex(size_t& i, size_t& col) const {
		i = col;
		++col;
		if (col > b_cols_) return false;
		return true;
	}

	Matrix Winograd::MulMatrixConveyorWinograd() {
		if (a_cols_ != b_rows_) {
			throw std::invalid_argument("Matrices are not compatible");
		}
		Vector row_factor;
		Vector column_factor;
		Matrix result(a_rows_, b_cols_);
		std::condition_variable cv;
		std::mutex m_factors;
		bool unblock = false;

		std::thread t1([&]() { CalculateMatrixWinograd(result); });
		std::thread t2([&]() {
			if (a_cols_ % 2) {
				AddElementsOddMatrix(result);
			}
			});

		std::thread t3([&]() {
			std::unique_lock<std::mutex> ul(m_factors);
			row_factor = RowFactor();
			column_factor = ColumnFactor();
			unblock = true;
			cv.notify_one();
			});

		std::thread t4([&]() {
			std::unique_lock<std::mutex> ul(m_factors);
			cv.wait(ul, [&] { return unblock; });
			AddFactors(row_factor, column_factor, result);
			});

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		return result;
	}

}  // namespace s21
