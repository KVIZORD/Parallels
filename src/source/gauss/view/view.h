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

  const std::vector<std::pair<std::string, std::function<void()>>>
      kMenuOptions = {
          {"Load matrix from file", [this] { LoadMatrixFromFile(); }},
          {"Input matrix from keyboard", [this] { InputMatrixFromKeyboard(); }},
          {"Random generation matrix",
           [this] { FillMatrixWithRandomValues(); }},
          {"Compare sync and async Gaussian elimination",
           [this] { CompareSolutionsSLAE(); }},
          {"Exit", [this] { Exit(); }}};

  const char kBoardSym = '-';
  const size_t kBoardSize = 30;

  explicit View(Controller &controller);

  void Exec();

private:
  void FillMatrixWithRandomValues();
  size_t ReadNumber();
  void PrintBoard();
  void Exit();
  void PrintMenu();
  void CompareSolutionsSLAE();
  void PrintInputPrompt();
  void PrintResultVector(std::vector<double> answers);
  double ReadMatrixElement();
  void InputMatrixFromKeyboard();
  void LoadMatrixFromFile();

  Matrix matrix_;
  Controller controller_;
  bool exit_ = false;
};

} // namespace s21

#endif // PARALLELS_SOURCE_GAUSS_VIEW_VIEW_H_
