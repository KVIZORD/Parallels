#ifndef PARALLELS_SOURCE_GAUSS_MODEL_GAUSS_H_
#define PARALLELS_SOURCE_GAUSS_MODEL_GAUSS_H_

#include <cstddef>
#include <thread>
#include <vector>

namespace s21 {

namespace Gauss {
using Matrix = std::vector<std::vector<double>>;

std::vector<double> SolveSync(Matrix matrix);
std::vector<double>
SolveAsync(Matrix matrix,
           size_t num_threads = std::thread::hardware_concurrency());

} // namespace Gauss

} // namespace s21

#endif // PARALLELS_SOURCE_GAUSS_MODEL_GAUSS_H_