#ifndef PARALLELS_SOURCE_WINOGRAD_CONTROLLER_S21_CONTROLLER_H_
#define PARALLELS_SOURCE_WINOGRAD_CONTROLLER_S21_CONTROLLER_H_

#include "../model/s21_winograd.h"

namespace s21 {
class Controller {
 public:
  Controller(){};
  Controller(const Matrix& a, const Matrix& b);
  Controller(const Controller& other) = delete;
  ~Controller();
  Controller& operator=(const Controller& other) = delete;
  WinogradData GetData() const;
  Matrix MulMatrix();
  Matrix MulMatrixWinograd();
  Matrix MulMatrixParallelWinograd(size_t threads);
  Matrix MulMatrixConveyorWinograd();
  void SetData(const Matrix& a, const Matrix& b);

 private:
  Winograd* model_ = nullptr;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_WINOGRAD_CONTROLLER_S21_CONTROLLER_H_