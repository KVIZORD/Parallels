#include "gauss/view/view.h"

#include <fstream>
#include <iostream>

namespace s21 {
View::View(Controller &controller) : controller_(controller) {}

void View::Exec() {
  while (!exit_) {
    try {
      PrintInputPrompt();
      size_t choice = ReadNumber();
      PrintBoard();

      if (choice > kMenuOptions.size() || choice == 0) {
        std::cout << "Incorrect choice" << std::endl;
      } else {
        kMenuOptions[choice - 1].second();
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
}

void View::PrintMenu() const {
  size_t counter = 1;
  for (auto elem : kMenuOptions) {
    std::cout << counter << ") " << elem.first << std::endl;
    ++counter;
  }
}

void View::PrintInputPrompt() const {
  PrintBoard();
  PrintMenu();
  PrintBoard();
  std::cout << "Input number: ";
}

size_t View::ReadNumber() const {
  size_t number;
  std::cin >> number;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::invalid_argument("Invalid input");
  }

  return number;
}

double View::ReadMatrixElement() const {
  double number;
  std::cin >> number;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::invalid_argument("Invalid input");
  }

  return number;
}

void View::InputMatrixFromKeyboard() {
  std::cout << "Input number of unknowns: ";
  size_t N = ReadNumber();

  matrix_.resize(N);
  for (size_t i = 0; i < N; ++i) {
    matrix_[i].resize(N + 1);
    for (size_t j = 0; j < N + 1; ++j) {
      std::cout << "[" << i << "]"
                << "[" << j << "] = ";
      matrix_[i][j] = ReadMatrixElement();
    }
  }
}

void View::LoadMatrixFromFile() {
  std::cout << "File path: ";
  std::string path;
  std::cin >> path;

  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::invalid_argument("Error opening file.");
  }

  size_t N;
  file >> N;

  matrix_.resize(N);
  for (size_t i = 0; i < N; ++i) {
    matrix_[i].resize(N + 1);
    for (size_t j = 0; j < N + 1; ++j) {
      if (!(file >> matrix_[i][j])) {
        throw std::invalid_argument("Error reading matrix element.");
      }
    }
  }

  std::cout << "Matrix loaded successfully from file." << std::endl;
}

void View::PrintBoard() const {
  for (size_t i = 0; i < kBoardSize; ++i) {
    std::cout << kBoardSym;
  }
  std::cout << std::endl;
}

void View::Exit() { exit_ = true; }

void View::PrintResultVector(std::vector<double> answers) const {
  for (double answer : answers) {
    std::cout << answer << " ";
  }
  std::cout << std::endl;
}

void View::FillMatrixWithRandomValues() {
  std::cout << "Input number of unknowns:" << std::endl;
  size_t size = ReadNumber();

  matrix_.resize(size);
  for (size_t i = 0; i < size; ++i) {
    matrix_[i].resize(size + 1);
    for (size_t j = 0; j < size + 1; ++j) {
      matrix_[i][j] = rand() % 1000;
    }
  }
}

void View::CompareSolutionsSLAE() const {
  if (matrix_.empty() || matrix_[0].empty()) {
    throw std::invalid_argument("Empty matrix");
  }

  std::cout << "Input the number of repetitions:" << std::endl;
  size_t count = ReadNumber();

  std::chrono::milliseconds time_sync;
  std::chrono::milliseconds time_async;
  std::vector<double> sync_result;
  std::vector<double> async_result;

  auto begin = std::chrono::steady_clock::now();
  for (size_t i = 0; i < count; ++i) {
    async_result = controller_.SolveGauseAsync(matrix_);
  }
  auto end = std::chrono::steady_clock::now();
  time_async =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

  begin = std::chrono::steady_clock::now();
  for (size_t i = 0; i < count; ++i) {
    sync_result = controller_.SolveGauseSync(matrix_);
  }
  end = std::chrono::steady_clock::now();
  time_sync =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

  std::cout << "Times of execution: " << std::endl;
  std::cout << "Synchronously:  " << time_sync.count() << "ms" << std::endl;
  std::cout << "Asynchronously: " << time_async.count() << "ms" << std::endl;

  PrintResultVector(sync_result);
  std::cout << std::endl;
  PrintResultVector(async_result);
}

}  // namespace s21