#include "gauss/model/gauss.h"

#include <mutex>
#include <stdexcept>

namespace s21 {
namespace Gauss {

void Eliminate(Matrix &matrix, size_t col, size_t start, size_t end) {
  size_t n = matrix.size();
  for (size_t i = start; i < end; ++i) {
    double factor;
    factor = matrix[i][col] / matrix[col][col];
    for (size_t j = col; j < n + 1; ++j) {
      matrix[i][j] -= factor * matrix[col][j];
    }
  }
}

std::vector<double> BackSubstitution(const Matrix &matrix) {
  size_t n = matrix.size();
  std::vector<double> solution(n);

  for (int i = n - 1; i >= 0; --i) {
    solution[i] = matrix[i][n];
    for (size_t j = i + 1; j < n; ++j) {
      solution[i] -= matrix[i][j] * solution[j];
    }
    solution[i] /= matrix[i][i];
  }

  return solution;
}

std::vector<double> SolveAsync(Matrix matrix, size_t num_threads) {
  size_t n = matrix.size();

  for (size_t i = 0; i < n - 1; ++i) {
    size_t chunk_size = (n - i - 1) / num_threads;
    std::vector<std::thread> threads;

    for (size_t t = 0; t < num_threads; ++t) {
      size_t start = i + 1 + t * chunk_size;
      size_t end = (t == num_threads - 1) ? n : i + 1 + (t + 1) * chunk_size;
      threads.push_back(
          std::thread(Eliminate, std::ref(matrix), i, start, end));
    }

    for (auto &t : threads) {
      t.join();
    }
  }

  return BackSubstitution(matrix);
}

std::vector<double> SolveSync(Matrix matrix) {
  size_t n = matrix.size();

  for (size_t i = 0; i < n - 1; ++i) {
    Eliminate(matrix, i, i + 1, n);
  }

  return BackSubstitution(matrix);
}

}  // namespace Gauss
}  // namespace s21