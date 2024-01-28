#include "s21_winograd.h"

namespace s21 {

	Matrix Winograd::MulMatrix() {
		return data_.a.MulMatrix(data_.b);
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
