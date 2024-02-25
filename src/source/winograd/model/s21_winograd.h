#ifndef PARALLELS_SOURCE_WINOGRAD_MODEL_S21_WINOGRAD_H_
#define PARALLELS_SOURCE_WINOGRAD_MODEL_S21_WINOGRAD_H_

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "winograd/common/s21_matrix.h"
#include "winograd/common/s21_winograd_data.h"

namespace s21 {

class Winograd {
  using Vector = std::vector<double>;

 public:
  std::mutex w_mutex;
  Winograd() = default;
  explicit Winograd(const WinogradData& data);
  WinogradData GetData() const;
  void SetData(const WinogradData& data);
  Matrix MulMatrix();
  Matrix MulMatrixWinograd();
  Matrix MulMatrixParallelWinograd(size_t threads);
  Matrix MulMatrixConveyorWinograd();

 private:
  WinogradData data_{};
  size_t a_rows_{0};
  size_t a_cols_{0};
  size_t b_rows_{0};
  size_t b_cols_{0};
  Vector RowFactor();
  Vector ColumnFactor();
  double RowFactorElement(size_t i);
  double ColumnFactorElement(size_t i);
  bool CheckMatrixIndex(size_t& i, size_t& j, size_t& row, size_t& col) const;
  bool CheckRawFactorIndex(size_t& i, size_t& row) const;
  bool CheckColumnFactorIndex(size_t& i, size_t& col) const;
  double CalculateMatrixElement(size_t i, size_t j, const Vector& row_factor,
                                const Vector& column_factor);
  template <typename T>
  T GetFromQueue(std::queue<T>& q, std::mutex& mtx,
                 std::condition_variable& cv);
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_WINOGRAD_MODEL_S21_WINOGRAD_H_