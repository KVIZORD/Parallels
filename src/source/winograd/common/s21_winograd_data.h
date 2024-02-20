#ifndef PARALLELS_SOURCE_WINOGRAD_COMMON_S21_WINOGRAD_DATA_H_
#define PARALLELS_SOURCE_WINOGRAD_COMMON_S21_WINOGRAD_DATA_H_

#include "s21_matrix.h"

namespace s21 {
struct WinogradData {
 public:
  WinogradData(){};
  WinogradData(const Matrix& a, const Matrix& b) {
    this->a = a;
    this->b = b;
  }

  // WinogradData& operator=(const WinogradData& other) {
  // 	if (this == &other) return *this;
  // 	a = other.a;
  // 	b = other.b;
  // 	return *this;
  // }
  Matrix a;
  Matrix b;
};
}  // namespace s21

#endif  // PARALLELS_SOURCE_WINOGRAD_COMMON_S21_WINOGRAD_DATA_H_