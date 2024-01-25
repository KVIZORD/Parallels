#include "graph.h"


explicit Graph::Graph(size_t size) 
    : matrix_(MatrixAdjacency(size, std::vector<size_t>(size, size_t{}))), size_(size) {
}

explicit Graph::Graph(size_t size, size_t init_value) 
    : matrix_(MatrixAdjacency(size, std::vector<size_t>(size, init_value))), size_(size) {
}

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

size_t Graph::GetValue(size_t from, size_t to) const {
    return matrix_[from][to];
}

void Graph::SetValue(size_t from, size_t to, size_t value) {
    matrix_[from][to] = value;
    matrix_[to][from] = value;
}

bool Graph::IsSquare(const MatrixAdjacency &matrix) {
    size_t rows = matrix_.size();
    size_t cols = matrix_.empty() ? 0 : matrix_[0].size();
    return rows == cols;
}


