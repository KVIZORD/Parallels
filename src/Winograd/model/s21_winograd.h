#ifndef PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
#define PARALLELS_WINOGRAD_MODEL_WINOGRAD_H

#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>

#include "../common/s21_matrix.h"
#include "../common/s21_winograd_data.h"

namespace s21 {

	class Winograd {
		using Vector = std::vector<double>;
	public:
		std::mutex w_mutex;
		Winograd() = default;
		explicit Winograd(const WinogradData& data);
		WinogradData GetData();
		void SetData(const WinogradData& data);
		Matrix MulMatrix();
		Matrix MulMatrixWinograd();
		Matrix MulMatrixConveyorWinograd();

	private:
		WinogradData data_{};
		size_t a_rows_{ 0 };
		size_t a_ñols_{ 0 };
		size_t b_rows_{ 0 };
		size_t b_cols_{ 0 };
		Vector RowFactor();
		Vector ColumnFactor();
		void CalculateMatrixWinograd(Matrix& result);
		void AddFactors(Vector& rowFactor, Vector& columnFactor, Matrix& result);
		void AddElementsOddMatrix(Matrix& result);
	};

} // namespace s21

#endif  // PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
