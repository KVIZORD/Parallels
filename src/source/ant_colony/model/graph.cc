#include "graph.h"

namespace s21 {

// Graph::Graph(size_t size) 
//     : matrix_(MatrixAdjacency(size, std::vector<size_t>(size, size_t{}))), size_(size) {
// }

// Graph::Graph(size_t size, size_t init_value) 
//     : matrix_(MatrixAdjacency(size, std::vector<size_t>(size, init_value))), size_(size) {
// }

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

size_t Graph::GetSize() const {
    return size_;
}

size_t Graph::GetValue(size_t from, size_t to) const {
    return matrix_[from][to];
}

void Graph::SetValue(size_t from, size_t to, size_t value) {
    matrix_[from][to] = value;
    matrix_[to][from] = value;
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

void Graph::Print() const {
    std::cout << "Matrix distances: " << std::endl;
    for (size_t i = 0; i < matrix_.size(); ++i) {
        for (size_t j = 0; j < matrix_.size(); ++j) {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

}  // namespace s21
