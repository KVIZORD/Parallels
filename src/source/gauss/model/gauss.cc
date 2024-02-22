#include "gauss/model/gauss.h"

namespace s21 {

void Gauss::Eliminate(Matrix &matrix, const std::vector<size_t> &rows) {
  for (const auto &row : rows) {
    for (size_t i = 0; i < row; ++i) {
      {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [&] { return row_processed_[i]; });
      }

      double factor = matrix[row][i] / matrix[i][i];

      for (size_t j = 0; j < matrix[row].size(); ++j) {
        matrix[row][j] -= factor * matrix[i][j];
      }
    }

    {
      std::unique_lock<std::mutex> lock(mtx_);
      row_processed_[row] = true;
      cv_.notify_all();
    }
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
  }

  return solution;
}

std::vector<double> Gauss::SolveAsync(Matrix matrix,
                                      std::size_t threads_count) {
  RemoveZeroesFromDiagonal(matrix);

  row_processed_.resize(matrix.size(), false);
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
  RemoveZeroesFromDiagonal(matrix);

  std::vector<size_t> rows;
  for (size_t i = 0; i < matrix.size(); ++i) {
    rows.push_back(i);
  }

  row_processed_.resize(matrix.size(), false);
  Eliminate(matrix, rows);

  return BackSubstitution(matrix);
}

void Gauss::RemoveZeroesFromDiagonal(Matrix &matrix) {
  for (size_t i = 0; i < matrix.size(); ++i) {
    if (matrix[i][i] == 0) {
      for (size_t j = i; j < matrix.size(); ++j) {
        if (matrix[j][i] != 0) {
          std::swap(matrix[i], matrix[j]);
          break;
        }
      }
    }
  }
}

} // namespace s21