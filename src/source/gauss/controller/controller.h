#ifndef PARALLELS_SOURCE_GAUSS_CONTROLLER_CONTROLLER_H_
#define PARALLELS_SOURCE_GAUSS_CONTROLLER_CONTROLLER_H_

#include <cstddef>
#include <thread>
#include <vector>

namespace s21 {
class Controller {
public:
  using Matrix = std::vector<std::vector<double>>;

  std::vector<double> SolveGauseSync(const Matrix &matrix);
  std::vector<double>
  SolveGauseAsync(const Matrix &matrix,
                  size_t num_threads = 4);
};
} // namespace s21

#endif // PARALLELS_SOURCE_GAUSS_CONTROLLER_CONTROLLER_H_