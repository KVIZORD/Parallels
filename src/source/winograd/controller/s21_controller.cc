#include "s21_controller.h"

namespace s21 {

Controller::Controller(const Matrix& a, const Matrix& b) {
  WinogradData data(a, b);
  model_ = new Winograd(data);
}

Controller::~Controller() {
  if (model_) {
    delete model_;
  }
}

WinogradData Controller::GetData() const { return model_->GetData(); }

Matrix Controller::MulMatrix() { return model_->MulMatrix(); }

Matrix Controller::MulMatrixWinograd() { return model_->MulMatrixWinograd(); }

Matrix Controller::MulMatrixConveyorWinograd() {
  return model_->MulMatrixConveyorWinograd();
}

void Controller::SetData(const Matrix& a, const Matrix& b) {
  WinogradData data(a, b);
  if (model_) model_->SetData(data);
}
}  // namespace s21
