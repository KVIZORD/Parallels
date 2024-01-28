#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_GRAPH_H
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_GRAPH_H

#include <vector>
#include <cstddef>
#include <stdexcept>
#include <iostream>


namespace s21 {

class Graph {
public:
    using MatrixAdjacency = std::vector<std::vector<size_t>>;

    Graph() = default;
    explicit Graph(size_t size);
    explicit Graph(size_t size, size_t init_value);
    Graph(const MatrixAdjacency &matrix);
    Graph(MatrixAdjacency &&matrix);

    size_t GetSize() const;
    size_t GetValue(size_t from, size_t to) const;
    void SetValue(size_t from, size_t to, size_t value);

    void Print() const;

private:
    MatrixAdjacency matrix_;
    size_t size_;

    bool IsSquare(const MatrixAdjacency &matrix);
};

}

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_GRAPH_H
