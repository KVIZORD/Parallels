#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_GRAPH_H
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_GRAPH_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace s21 {

class Graph {
 public:
  using MatrixAdjacency = std::vector<std::vector<size_t>>;

  Graph() = default;
  explicit Graph(const MatrixAdjacency &matrix);
  explicit Graph(MatrixAdjacency &&matrix);

  size_t GetSize() const;
  size_t GetValue(size_t from, size_t to) const;
  void SetMatrix(MatrixAdjacency &&matrix);

 private:
  MatrixAdjacency matrix_;
  size_t size_;

  bool IsSquare(const MatrixAdjacency &matrix);
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_GRAPH_H
