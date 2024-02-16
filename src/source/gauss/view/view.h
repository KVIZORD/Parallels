#ifndef PARALLELS_SOURCE_GAUSS_VIEW_VIEW_H_
#define PARALLELS_SOURCE_GAUSS_VIEW_VIEW_H_

#include <functional>
#include <gauss/controller/controller.h>
#include <string>
#include <vector>

namespace s21 {

class View {
public:
  using Matrix = std::vector<std::vector<double>>;

  enum class SLAEMethod { kGaussAsync, kGaussSync };

  const std::vector<std::pair<std::string, std::function<void()>>> kMenu = {
      {"Load matrix from file", [] { return; }},
      {"Input matrix from keyboard", [] { return; }},
      {"Compare sync and async Gaussian elimination",
       [this] { CompareSolutionsSLAE(); }},
      {"Exit", [this] { Exit(); }}};
  const char kBoardSym = '-';
  const size_t kBoardSize = 30;

  explicit View(Controller &controller);

  void Exec();

private:
  size_t ReadNumber();
  void PrintBoard();
  void Exit();
  void PrintMenu();
  void CompareSolutionsSLAE();
  void PrintInputPromt();
  std::chrono::milliseconds
  MeasureTime(std::function<std::vector<double>()> solve_slae);
  std::vector<double> RunMultiple(size_t count, SLAEMethod method);

  Matrix matrix_ = {{43, 23, 12, 56, 78, 34, 21, 65, 76, 22, 90},
                   {98, 55, 33, 11, 87, 44, 31, 20, 78, 42, 69},
                   {15, 29, 88, 66, 37, 19, 82, 47, 54, 73, 10},
                   {41, 85, 27, 63, 52, 18, 79, 35, 91, 14, 68},
                   {16, 77, 25, 49, 83, 38, 92, 71, 39, 57, 24},
                   {74, 28, 62, 86, 13, 51, 30, 67, 45, 81, 97},
                   {75, 48, 26, 72, 84, 36, 70, 53, 99, 46, 80},
                   {58, 94, 40, 59, 93, 64, 89, 50, 95, 60, 96},
                   {17, 23, 23, 7, 3, 9, 6, 2, 4, 8, 1},
                   {32, 23, 23, 7, 3, 9, 6, 2, 4, 8, 1}};
  Controller controller_;
  bool exit_ = false;
};

} // namespace s21

#endif // PARALLELS_SOURCE_GAUSS_VIEW_VIEW_H_
