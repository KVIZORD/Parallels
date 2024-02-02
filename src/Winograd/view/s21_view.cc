#include "s21_view.h"
#include <mutex>
#include <thread>

namespace s21 {
	View::~View() {
		if (controller_) {
			delete controller_;
		}
	}

	void View::Run() {
		try {
			FillMatrix();
			int iter = CheckCorrectNumberInput("Input number of iteration: ");


			//////////////////////////////////////////////////////////////////////////////////////
			/// Простое умножение
			//////////////////////////////////////////////////////////////////////////////////////////
			double time = MulMatrix(iter);
			std::cout << "\nTime execution = " << time << " milliseconds\n__________________________\n";


			//////////////////////////////////////////////////////////////////////////////////////
			/// умножение виноград
 			//////////////////////////////////////////////////////////////////////////////////////////
			Matrix temp = controller_->MulMatrixWinograd();
			temp.Print();
			const auto start{ std::chrono::system_clock::now() };
			for (size_t i = 0; i < iter; ++i) {
				controller_->MulMatrixWinograd();
			}
			const auto finish{ std::chrono::system_clock::now() };
			std::cout << "\nTime execution = " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " milliseconds\n_______________\n";


			//////////////////////////////////////////////////////////////////////////////////////
			/// умножение виноград параллель
			//////////////////////////////////////////////////////////////////////////////////////////
			std::cout << "\nInput threads count: ";
			int threads = CheckCorrectNumberInput("");
			int sss = iter / threads;

			auto func = [&]() {
				for (size_t a = 0; a < sss; a++)
				{
					controller_->MulMatrixWinograd();
				}
				};

			const auto start1{ std::chrono::system_clock::now() };
			std::vector<std::thread> list;
			for (size_t a = 0; a < threads; a++)
			{
				list.push_back(std::thread(func));
			}

			for (size_t i = 0; i < list.size(); i++)
			{
				list[i].join();
			}
			const auto finish1{ std::chrono::system_clock::now() };

			temp.Print();
			std::cout << "Time execution = " << std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1).count() << " milliseconds\n";




			//////////////////////////////////////////////////////////////////////////////////////
			/// умножение виноград конвеер
			//////////////////////////////////////////////////////////////////////////////////////////

			auto func1 = [&]() {
				for (size_t a = 0; a < sss; a++)
				{
					controller_->MulMatrixConveyorWinograd();					
				}
				};
			Matrix temp1 = controller_->MulMatrixConveyorWinograd();
			temp1.Print();
			
			std::vector<std::thread> list2;
			//std::mutex mtx;
			const auto start2{ std::chrono::system_clock::now() };
			for (size_t a = 0; a < threads; a++)
			{
				list2.push_back(std::thread(func1));
			}

			for (size_t i = 0; i < list2.size(); i++)
			{
				list2[i].join();
			}


			const auto finish2{ std::chrono::system_clock::now() };

			std::cout << "Time execution = " << std::chrono::duration_cast<std::chrono::milliseconds>(finish2 - start2).count() << " milliseconds\n";


		}
		catch (const std::exception& e) {
			std::cout << e.what();
		}
	}



	int View::CheckCorrectNumberInput(std::string message) {
		std::cout << message;
		int input{};
		std::cin >> input;
		if (std::cin.fail() || input < 1) {
			std::cin.clear();
			std::cin.ignore();
			throw std::invalid_argument("Incorrect input data");
		}
		return input;
	}

	double View::MatrixElementInput() {
		double input{};
		std::cin >> input;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			throw std::invalid_argument("Incorrect input data");
		}
		return input;
	}

	void View::FillMatrix() {
		while (true) {
			std::cout << "Select matrix fill method: \n";
			std::cout << "1) Fill matrix from console\n";
			std::cout << "2) Random fill matrix\n";
			int method_choise{ 0 };
			method_choise = CheckCorrectNumberInput("");
			if (method_choise == 1) {
				InputFromConsole();
				break;
			}
			if (method_choise == 2) {
				FillRandom();
				break;
			}
			std::cout << "\nSelected method should be 1 or 2. Try again!\n\n";
		}
	}

	void View::InputFromConsole() {
		int row1 = CheckCorrectNumberInput("Input the number of rows of the first matrix : ");
		int col1 = CheckCorrectNumberInput("Input the number of columns of the first matrix : ");
		std::cout << "Input first matrix elements\n";
		Matrix a(row1, col1);
		for (size_t i = 0; i < row1; ++i) {
			for (size_t j = 0; j < col1; ++j) {
				a(i, j) = MatrixElementInput();
			}
		}

		int row2 = CheckCorrectNumberInput("Input the number of rows of the second matrix : ");
		int col2 = CheckCorrectNumberInput("Input the number of columns of the second matrix : ");
		std::cout << "Input second matrix elements\n";
		Matrix b(row2, col2);
		for (size_t i = 0; i < row2; ++i) {
			for (size_t j = 0; j < col2; ++j) {
				b(i, j) = MatrixElementInput();
			}
		}
		controller_ = new Controller(a, b);
	}

	void View::FillRandom() {
		int row1 = CheckCorrectNumberInput("Input the number of rows of the first matrix : ");
		int col1 = CheckCorrectNumberInput("Input the number of columns of the first matrix : ");
		Matrix a(row1, col1);
		a.RandomMatrix();

		int row2 = CheckCorrectNumberInput("Input the number of rows of the second matrix : ");
		int col2 = CheckCorrectNumberInput("Input the number of columns of the second matrix : ");
		Matrix b(row2, col2);
		b.RandomMatrix();

		controller_ = new Controller(a, b);
	}


	double View::MulMatrix(int iter) {
		const auto start{ std::chrono::system_clock::now() };
		for (size_t i = 0; i < iter; ++i) {
			controller_->MulMatrix();
		}
		const auto finish{ std::chrono::system_clock::now() };
		Matrix aaa = controller_->MulMatrix();
		aaa.Print();
		return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
	}
}
