#ifndef PARALLELS_SOURCE_ANT_COLONY_COMMON_ANT_H
#define PARALLELS_SOURCE_ANT_COLONY_COMMON_ANT_H

#include <vector>
#include <random>

#include "graph.h"
#include "path_structure.h"
#include "pheromone.h"

namespace s21 {

class Ant {
public:
    Ant(const Graph &distances, std::mt19937 &gen, double pheromone_amount);

    TsmResult &GetPath() const;
    double GetPheromoneAmount() const;
    bool Move(const Pheromone &pheromones)

private:
    Graph distances_;
    std::mt19937 &gen_;
    double pheromone_amount_;
    std::vector<size_t> used_vertex_;
    TsmResult path_{};

    double GetDistance(size_t from, size_t to) const;
    size_t GetFirstVetex();
    size_t GetLastVertex();
    std::vector<double> GetProbabilities(const Pheromone &pheromones, const std::vector<size_t> &neighbors);
    double GetRandomProbability();
    std::vector<size_t> GetPossibleNeighbors();
    double CalcSummaryWeight(const Pheromone &pheromones, const std::vector<size_t> &neighbors);

};

}

#endif  // PARALLELS_SOURCE_ANT_COLONY_COMMON_ANT_H
