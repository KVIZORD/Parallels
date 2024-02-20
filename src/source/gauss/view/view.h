#ifndef PARALLELS_SOURCE_GAUSS_VIEW_VIEW_H_
#define PARALLELS_SOURCE_GAUSS_VIEW_VIEW_H_

#include <gauss/controller/controller.h>

#include <functional>
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
  size_t ReadNumber() const;
  void PrintBoard() const;
  void PrintMenu() const;
  void CompareSolutionsSLAE() const;
  void PrintInputPrompt() const;
  void PrintResultVector(std::vector<double> answers) const;
  double ReadMatrixElement() const;
  void FillMatrixWithRandomValues();
  void InputMatrixFromKeyboard();
  void LoadMatrixFromFile();
  void Exit();

  Matrix matrix_;
  Controller controller_;
  bool exit_ = false;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_GAUSS_VIEW_VIEW_H_
