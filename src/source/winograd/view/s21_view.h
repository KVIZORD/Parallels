#ifndef PARALLELS_WINOGRAD_VIEW_VIEW_H
#define PARALLELS_WINOGRAD_VIEW_VIEW_H

#include <chrono>
#include <functional>

#include "../controller/s21_controller.h"

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
  void PrintMulMatrixParallel(const std::string& message, int iter,
                                    std::function<Matrix(size_t)> operation);
  void PrintRow(char a, size_t length);
  void PrintDataMatrix();
  void PrintResult(const Matrix& matrix, Time start, Time finish);
  std::vector<size_t> IterForThreads(size_t iter, size_t threads);
};

}  // namespace s21

#endif  // PARALLELS_WINOGRAD_VIEW_VIEW_H
