#ifndef PARALLELS_SOURCE_ANT_COLONY_VIEW_VIEW_H
#define PARALLELS_SOURCE_ANT_COLONY_VIEW_VIEW_H

#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "ant_colony/controller/controller.h"
#include "ant_colony/model/tsm_result.h"

namespace s21 {

class View {
 public:
  using Matrix = std::vector<std::vector<size_t>>;

  enum GraphLoadMethod {
    kFromConsole,
    kFromFile,
  };

  enum TsmSolveMethod {
    kSync,
    kAsync,
  };

  explicit View(Controller &controller);
  void Exec();

 private:
  Controller &controller_;

  void CompareSolutionsTsm();
  void LoadGraphFromConsole();
  void LoadGraphFromFile();
  std::chrono::milliseconds MeasureTime(std::function<TsmResult()> solve_tsm);
  void OutputSolutionTsm();
  void PrintPathResult(const TsmResult &path_sync, const TsmResult &path_async);
  std::string ReadLine(std::istream &in = std::cin);
  Matrix ReadMatrix(size_t size, std::istream &in = std::cin);
  long long ReadNumber(std::istream &in = std::cin);
  TsmResult RunMultiple(size_t count, TsmSolveMethod method);
  void ShowMenu();
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_VIEW_VIEW_H
