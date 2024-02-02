#ifndef PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
#define PARALLELS_WINOGRAD_MODEL_WINOGRAD_H

#include <vector>
#include <iostream>
#include <mutex>
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
		Vector RowFactor();
		Vector ColumnFactor();
		void CalculateMatrixWinograd(Vector rowFactor, Vector columnFactor, Matrix& result);
		void AddElementsOddMatrix(Matrix& result);
	};

} // namespace s21

#endif  // PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
