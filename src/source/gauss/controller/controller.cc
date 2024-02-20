#include <gauss/controller/controller.h>

#include "gauss/model/gauss.h"

namespace s21 {

std::vector<double> Controller::SolveGauseSync(const Matrix &matrix) const {
  return Gauss::SolveSync(matrix);
}

std::vector<double> Controller::SolveGauseAsync(const Matrix &matrix,
                                                size_t num_threads) const {
  return Gauss::SolveAsync(matrix, num_threads);
}

}  // namespace s21