#ifndef PARALLELS_WINOGRAD_CONTROLLER_CONTROLLER_H
#define PARALLELS_WINOGRAD_CONTROLLER_CONTROLLER_H

#include "../model/s21_winograd.h"

namespace s21 {
	class Controller
	{
	public:
		Controller() {};
		explicit Controller(const Matrix& a, const Matrix& b);
		~Controller();
		WinogradData GetData();
		Matrix MulMatrix();
		void SetData(const Matrix& a, const Matrix& b);
		//void SetValue(double value);

	private:
		Winograd* model_ = nullptr;
	};

} // namespace s21

#endif  // PARALLELS_WINOGRAD_CONTROLLER_CONTROLLER_H