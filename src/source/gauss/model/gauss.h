#ifndef PARALLELS_SOURCE_GAUSS_MODEL_GAUSS_H_
#define PARALLELS_SOURCE_GAUSS_MODEL_GAUSS_H_

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <thread>
#include <vector>

namespace s21 {

class Gauss {
 public:
  using Matrix = std::vector<std::vector<double>>;

  std::vector<double> SolveSync(Matrix matrix);
  std::vector<double> SolveAsync(
      Matrix matrix,
      std::size_t num_threads = std::thread::hardware_concurrency());

 private:
  void Eliminate(Matrix &matrix, const std::vector<std::size_t> &rows);
  std::vector<double> BackSubstitution(const Matrix &matrix);
  void RemoveZeroesFromDiagonal(Matrix &matrix);

  std::vector<bool> row_processed_;
  std::condition_variable cv_;
  std::mutex mtx_;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_GAUSS_MODEL_GAUSS_H_