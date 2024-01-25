#ifndef PARALLELS_SOURCE_ANT_COLONY_COMMON_GRAPH_H
#define PARALLELS_SOURCE_ANT_COLONY_COMMON_GRAPH_H

#include <vector>

class Graph {
public:
    using MatrixAdjacency = std::vector<std::vector<size_t>>;

    Graph() = default;
    explicit Graph(size_t size);
    explicit Graph(size_t size, size_t init_value);
    Graph(const MatrixAdjacency &matrix);
    Graph(MatrixAdjacency &&matrix);

    size_t GetValue(size_t from, size_t to) const;
    void SetValue(size_t from, size_t to, size_t value);

private:
    MatrixAdjacency matrix_;
    size_t size_;

    bool IsSquare(const MatrixAdjacency &matrix);
}

#endif  // PARALLELS_SOURCE_ANT_COLONY_COMMON_ANT_H




