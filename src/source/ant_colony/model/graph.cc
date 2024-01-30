#include "graph.h"

namespace s21 {

Graph::Graph(const MatrixAdjacency &matrix) {
  if (!IsSquare(matrix)) {
    throw std::invalid_argument("Matrix is not square");
  }

  matrix_ = matrix;
  size_ = matrix_.size();
}

Graph::Graph(MatrixAdjacency &&matrix) {
  if (!IsSquare(matrix)) {
    throw std::invalid_argument("Matrix is not square");
  }

  matrix_ = std::move(matrix);
  size_ = matrix_.size();
}

size_t Graph::GetSize() const { return size_; }

size_t Graph::GetValue(size_t from, size_t to) const {
  return matrix_[from][to];
}

void Graph::SetMatrix(MatrixAdjacency &&matrix) {
  if (!IsSquare(matrix)) {
    throw std::invalid_argument("Matrix is not square");
  }

  matrix_ = matrix;
  size_ = matrix_.size();
}

bool Graph::IsSquare(const MatrixAdjacency &matrix) {
  size_t rows = matrix.size();
  size_t cols = matrix.empty() ? 0 : matrix[0].size();
  return rows == cols;
}

}  // namespace s21
