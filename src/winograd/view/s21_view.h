#ifndef PARALLELS_SOURCE_WINOGRAD_VIEW_S21_VIEW_H_
#define PARALLELS_SOURCE_WINOGRAD_VIEW_S21_VIEW_H_

#include <chrono>
#include <functional>

#include "winograd/controller/s21_controller.h"

namespace s21 {
class View {
  using Time = std::chrono::system_clock::time_point;

 public:
  View() = default;
  ~View();
  void Run();

 private:
  Controller* controller_ = nullptr;
  int CheckCorrectNumberInput(const std::string& message) const;
  double MatrixElementInput();
  void FillMatrix();
  void InputFromConsole();
  void FillRandom();
  void PrintMulMatrix(const std::string& message, int iter,
                      std::function<Matrix()> operation);
  void MulMatrixParallelManual(const std::string& message, int iter,
                               std::function<Matrix(size_t)> operation);
  void MulMatrixParallelCore(const std::string& message, int iter,
                             std::function<Matrix(size_t)> operation);
  void PrintRow(char a, size_t length);
  void PrintDataMatrix();
  void PrintResult(const Matrix& matrix, Time start, Time finish);
  void PrintMatrixParallel(int threads, int iter,
                           std::function<Matrix(size_t)> operation);
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_WINOGRAD_VIEW_S21_VIEW_H_