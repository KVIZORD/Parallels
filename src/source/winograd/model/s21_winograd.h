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
  void CalculateMatrixWinograd(Matrix& result);
  void AddFactors(const Vector& rowFactor, const Vector& columnFactor,
                  Matrix& result);
  void AddElementsOddMatrix(Matrix& result);
  bool CheckMatrixIndex(size_t& i, size_t& j, size_t& row, size_t& col) const;
  bool CheckRawFactorIndex(size_t& i, size_t& row) const;
  bool CheckColumnFactorIndex(size_t& i, size_t& col) const;
  double CalculateMatrixElement(size_t i, size_t j, Vector& row_factor, Vector& column_factor);
};

}  // namespace s21

#endif  // PARALLELS_WINOGRAD_MODEL_WINOGRAD_H
