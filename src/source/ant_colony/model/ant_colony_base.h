#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_BASE_H
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_BASE_H

#include <random>
#include <vector>

#include "ant.h"
#include "graph.h"
#include "pheromone.h"
#include "tsm_result.h"

namespace s21 {

class AntColonyBase {
 public:
  const double kPheromoneQuantity = 15.0;
  const double kPheromoneEvaporationRate = 0.1;
  const double kPheromonInitialLevel = 1;

  AntColonyBase(Graph &graph, size_t count_colony, size_t size_colony);
  virtual TsmResult Solve() = 0;

 protected:
  Graph &graph_;
  size_t count_colony_;
  size_t size_colony_;
  std::vector<Ant> ant_colony{};
  std::random_device rd_{};
  std::mt19937 gen_{rd_()};

  TsmResult TravelsAnt(Ant &ant, const Pheromone &pheromones);
  void UpdateMinPath(TsmResult &min_path, const TsmResult &path) const;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_BASE_H
