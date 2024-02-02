#ifndef PARALLELS_WINOGRAD_VIEW_VIEW_H
#define PARALLELS_WINOGRAD_VIEW_VIEW_H

#include "../controller/s21_controller.h"
#include <chrono>

namespace s21 {
class View
{	
	public:
		View() = default;
		~View(); 
		void Run();

	private:
		int CheckCorrectNumberInput(std::string message);
		double MatrixElementInput();
		void FillMatrix();
		void InputFromConsole();
		void FillRandom();
		double MulMatrix(int iter);
		Controller* controller_ = nullptr;		
};

} // namespace s21

#endif  // PARALLELS_WINOGRAD_VIEW_VIEW_H
