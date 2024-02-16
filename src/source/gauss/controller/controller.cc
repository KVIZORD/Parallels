#include "gauss/model/gauss.h"
#include <gauss/controller/controller.h>

namespace s21 {

std::vector<double> Controller::SolveGauseSync(const Matrix &matrix) {
  return Gauss::SolveSync(matrix);
}

std::vector<double> Controller::SolveGauseAsync(const Matrix &matrix, size_t num_threads) {
  return Gauss::SolveAsync(matrix, num_threads);
}

} // namespace s21