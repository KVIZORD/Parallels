#ifndef PARALLELS_WINOGRAD_CONTROLLER_CONTROLLER_H
#define PARALLELS_WINOGRAD_CONTROLLER_CONTROLLER_H

#include "../model/s21_winograd.h"

namespace s21 {
	class Controller {
	public:
		Controller() {};
		Controller(const Matrix& a, const Matrix& b);
		~Controller();
		WinogradData GetData();
		Matrix MulMatrix();
		Matrix MulMatrixWinograd();
		Matrix MulMatrixConveyorWinograd();
		void SetData(const Matrix& a, const Matrix& b);		

	private:
		Winograd* model_ = nullptr;
	};

} // namespace s21

#endif  // PARALLELS_WINOGRAD_CONTROLLER_CONTROLLER_H