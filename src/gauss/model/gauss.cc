#include "gauss/model/gauss.h"

#include <cmath>

namespace s21 {

void Gauss::Eliminate(Matrix &matrix, const std::vector<size_t> &rows) {
  for (size_t col = 0; col < matrix.size(); ++col) {
    {
      std::unique_lock<std::mutex> lock(mtx_);
      prev_col_processed_.wait(lock, [&] {
        return col == 0 || col_processed_[col - 1] == matrix.size() - col;
      });

      for (size_t j = col; j < matrix.size(); ++j) {
        if (std::abs(matrix[j][col]) > std::abs(matrix[col][col])) {
          std::swap(matrix[col], matrix[j]);
        }
      }
    }

    for (const auto &row : rows) {
      if (col >= row) {
        std::unique_lock<std::mutex> lock(mtx_);
        row_processed_[row] = true;
        pivot_row_processed_.notify_all();
        continue;
      }

      std::unique_lock<std::mutex> wait_lock(mtx_);
      pivot_row_processed_.wait(wait_lock, [&] { return row_processed_[col]; });
      wait_lock.unlock();

      double factor = matrix[row][col] / matrix[col][col];
      for (size_t j = 0; j < matrix[row].size(); ++j) {
        matrix[row][j] -= factor * matrix[col][j];
      }

      std::unique_lock<std::mutex> col_processed_lock(mtx_);
      col_processed_[col] += 1;
      col_processed_lock.unlock();
    }

    std::unique_lock<std::mutex> notify_lock(mtx_);
    prev_col_processed_.notify_all();
    notify_lock.unlock();
  }
}

std::vector<double> Gauss::BackSubstitution(const Matrix &matrix) {
  int n = matrix.size();
  std::vector<double> solution(n, 0.0);

  for (int i = n - 1; i >= 0; --i) {
    double sum = 0.0;
    for (int j = i + 1; j < n; ++j) {
      sum += matrix[i][j] * solution[j];
    }
    solution[i] = (matrix[i][n] - sum) / matrix[i][i];

    if (std::isnan(solution[i])) {
      solution.clear();
      break;
    }
  }

  return solution;
}

std::vector<double> Gauss::SolveAsync(Matrix matrix,
                                      std::size_t threads_count) {
  if (threads_count == 0) {
    throw std::invalid_argument("Incorrect threads count");
  }

  row_processed_.resize(matrix.size(), false);
  col_processed_.resize(matrix.size(), 0);

  std::vector<std::thread> threads;
  std::vector<std::vector<size_t>> rows(threads_count, std::vector<size_t>());

  for (size_t i = 0; i < matrix.size(); ++i) {
    rows[(i) % threads_count].push_back(i);
  }

  for (size_t i = 0; i < threads_count; ++i) {
    threads.push_back(std::thread(
        [this](Matrix &matrix, const std::vector<size_t> &rows) {
          this->Eliminate(matrix, rows);
        },
        std::ref(matrix), std::cref(rows[i])));
  }

  for (auto &t : threads) {
    t.join();
  }

  return BackSubstitution(matrix);
}

std::vector<double> Gauss::SolveSync(Matrix matrix) {
  row_processed_.resize(matrix.size(), false);
  col_processed_.resize(matrix.size(), 0);

  std::vector<size_t> rows;
  for (size_t i = 0; i < matrix.size(); ++i) {
    rows.push_back(i);
  }

  Eliminate(matrix, rows);

  return BackSubstitution(matrix);
}

}  // namespace s21