#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_H_
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_H_

#include <random>
#include <vector>

#include "graph.h"
#include "pheromone.h"
#include "tsm_result.h"

namespace s21 {

class Ant {
 public:
  const double kAlpha = 1;
  const double kBetta = 1;
  const double kDistance = 1;

  Ant(const Graph &distances, std::mt19937 &gen, double pheromone_amount);

  const TsmResult &GetPath() const;
  double GetPheromoneAmount() const;
  bool Move(const Pheromone &pheromones);

 private:
  Graph distances_;
  std::mt19937 &gen_;
  double pheromone_amount_;
  std::vector<bool> used_vertex_;
  TsmResult path_{};

  double GetDistance(size_t from, size_t to) const;
  size_t GetFirstVetex();
  size_t GetLastVertex();
  std::vector<double> GetProbabilities(const Pheromone &pheromones,
                                       const std::vector<size_t> &neighbors);
  double GetRandomProbability();
  std::vector<size_t> GetPossibleNeighbors();
  double CalcSummaryWeight(const Pheromone &pheromones,
                           const std::vector<size_t> &neighbors);
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_H_