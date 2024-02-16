#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_PHEROMONE_H_
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_PHEROMONE_H_

#include <cstddef>
#include <vector>
#include <thread>

namespace s21 {

namespace Gauss {
using Matrix = std::vector<std::vector<double>>;
const double kEpsilon = 1e-10;

std::vector<double> SolveSync(Matrix matrix);
std::vector<double>
SolveAsync(Matrix matrix,
           size_t num_threads = std::thread::hardware_concurrency());

} // namespace Gauss

} // namespace s21

#endif // PARALLELS_SOURCE_ANT_COLONY_MODEL_PHEROMONE_H_