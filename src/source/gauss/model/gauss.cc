#include "gauss/model/gauss.h"
#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <mutex>

namespace s21 {
namespace Gauss {

std::condition_variable cv;

void Eliminate(Matrix &matrix, const std::vector<size_t> &rows,
               std::vector<bool> &row_processed,
               std::vector<std::mutex> &mutexes) {
  for (auto &row : rows) {
    std::unique_lock<std::mutex> lock(mutexes[row]);
    for (size_t i = 0; i < row; ++i) {

      size_t pivot_str = i;

      cv.wait(lock, [&] { return row_processed[pivot_str]; });

      double factor = matrix[row][i] / matrix[pivot_str][pivot_str];

      for (size_t j = 0; j < matrix[row].size(); ++j) {
        matrix[row][j] -= factor * matrix[pivot_str][j];
      }
    }

    row_processed[row] = true;
    cv.notify_all();
  }
}

std::vector<double> BackSubstitution(const Matrix &matrix) {
  int n = matrix.size();
  std::vector<double> solution(n, 0.0);

  for (int i = n - 1; i >= 0; --i) {
    double sum = 0.0;
    for (int j = i + 1; j < n; ++j) {
      sum += matrix[i][j] * solution[j];
    }
    solution[i] = (matrix[i][n] - sum) / matrix[i][i];
  }

  return solution;
}

std::vector<double> SolveAsync(Matrix matrix, size_t threads_count) {
  std::vector<bool> row_proccessed(matrix.size(), false);
  std::vector<std::mutex> mutexes(matrix.size());
  std::vector<std::thread> threads;
  std::vector<std::vector<size_t>> rows(threads_count, std::vector<size_t>());
  row_proccessed[0] = true;

  for (size_t i = 1; i < matrix.size(); ++i) {
    rows[(i - 1) % threads_count].push_back(i);
  }

  for (size_t i = 0; i < threads_count; ++i) {
    threads.push_back(std::thread(Eliminate, std::ref(matrix),
                                  std::cref(rows[i]), std::ref(row_proccessed),
                                  std::ref(mutexes)));
  }

  for (auto &t : threads) {
    t.join();
  }

  return BackSubstitution(matrix);
}

std::vector<double> SolveSync(Matrix matrix) {
  std::vector<size_t> rows;
  for (size_t i = 1; i < matrix.size(); ++i) {
    rows.push_back(i);
  }

  std::vector<bool> row_proccessed(matrix.size(), false);
  std::vector<std::mutex> mutexes(matrix.size());
  row_proccessed[0] = true;

  Eliminate(matrix, rows, row_proccessed, mutexes);

  return BackSubstitution(matrix);
}

} // namespace Gauss
} // namespace s21