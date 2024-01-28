#ifndef PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
#define PARALLELS_WINOGRAD_MODEL_WINOGRAD_H

#include <vector>
#include <iostream>
#include "../common/s21_matrix.h"
#include "../common/s21_winograd_data.h"


namespace s21 {
	

	class Winograd {
	public:
		Winograd() = default;
		explicit Winograd(const WinogradData& data);
		WinogradData GetData();
		void SetData(const WinogradData& data);
		Matrix MulMatrix();


	private:
		WinogradData data_{};
		//size_t iter_;
	};

} // namespace s21

#endif  // PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
