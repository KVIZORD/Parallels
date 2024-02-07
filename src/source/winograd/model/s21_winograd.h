#ifndef PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
#define PARALLELS_WINOGRAD_MODEL_WINOGRAD_H

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "../common/s21_matrix.h"
#include "../common/s21_winograd_data.h"

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
  Matrix MulMatrixConveyorWinograd();

 private:
  WinogradData data_{};
  size_t a_rows_{0};
  size_t a_cols_{0};
  size_t b_rows_{0};
  size_t b_cols_{0};
  Vector RowFactor();
  Vector ColumnFactor();
  void CalculateMatrixWinograd(Matrix& result);
  void AddFactors(const Vector& rowFactor, const Vector& columnFactor,
                  Matrix& result);
  void AddElementsOddMatrix(Matrix& result);
};

}  // namespace s21

#endif  // PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
