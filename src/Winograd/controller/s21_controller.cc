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
	WinogradData Controller::GetData()	{
		return model_->GetData();
	}

	Matrix Controller::MulMatrix() {
		return model_->MulMatrix();
	}
	void Controller::SetData(const Matrix& a, const Matrix& b) {
		WinogradData data(a, b);
		if(model_) model_->SetData(data);		
	}
}
