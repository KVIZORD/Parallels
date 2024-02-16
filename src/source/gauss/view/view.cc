#include "gauss/view/view.h"
#include "view.h"
#include <iostream>

namespace s21 {
View::View(Controller &controller) : controller_(controller) {}

void View::Exec() {
  while (!exit_) {
    PrintInputPromt();
    size_t choice = ReadNumber();
    PrintBoard();

    if (choice > kMenu.size()) {
      std::cout << "ERROR" << std::endl;
    } else {
      kMenu[choice - 1].second();
    }
  }
}

void View::PrintMenu() {
  size_t counter = 1;
  for (auto elem : kMenu) {
    std::cout << counter << ") " << elem.first << std::endl;
    ++counter;
  }
}

void View::PrintInputPromt() {
  PrintBoard();
  PrintMenu();
  PrintBoard();
  std::cout << "Input number: ";
}

size_t View::ReadNumber() {
  size_t number;
  std::cin >> number;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    number = 0;
  }

  return number;
}

void View::PrintBoard() {
  for (size_t i = 0; i < kBoardSize; ++i) {
    std::cout << kBoardSym;
  }
  std::cout << std::endl;
}

void View::Exit() { exit_ = true; }

std::vector<double> View::RunMultiple(size_t count, SLAEMethod method) {
  std::vector<double> result;
  for (size_t i = 0; i < count; i++) {
    result = (method == SLAEMethod::kGaussAsync)
                 ? controller_.SolveGauseAsync(matrix_)
                 : controller_.SolveGauseSync(matrix_);
  }

  return result;
}

void View::CompareSolutionsSLAE() {
  std::cout << "Input the number of repetitions:" << std::endl;
  size_t count = ReadNumber();

  auto time_sync = MeasureTime(
      [&count, this]() { return RunMultiple(count, SLAEMethod::kGaussSync); });
  auto time_async = MeasureTime(
      [&count, this]() { return RunMultiple(count, SLAEMethod::kGaussAsync); });

  std::cout << "Times of execution: " << std::endl;
  std::cout << "\t- synchronously:  " << time_sync.count() << "ms" << std::endl;
  std::cout << "\t- asynchronously: " << time_async.count() << "ms"
            << std::endl;
}

std::chrono::milliseconds
View::MeasureTime(std::function<std::vector<double>()> solve_slae) {
  auto begin = std::chrono::steady_clock::now();
  solve_slae();
  auto end = std::chrono::steady_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

} // namespace s21