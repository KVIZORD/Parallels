#include "ant_colony_sync.h"

namespace s21 {

AntColonySync::AntColonySync(Graph &graph, size_t count_colony,
                             size_t size_colony)
    : AntColonyBase(graph, count_colony, size_colony) {}

TsmResult AntColonySync::Solve() {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();
  if (graph_.GetSize() == 0) {
    return min_path;
  }

  for (size_t i = 0; i < count_colony_; ++i) {
    Pheromone pheromones(graph_.GetSize(), kPheromonInitialLevel,
                         kPheromoneEvaporationRate);

    for (size_t j = 0; j < size_colony_; ++j) {
      Ant ant(graph_, gen_, kPheromoneQuantity);
      const TsmResult path = TravelsAnt(ant, pheromones);
      pheromones.Update(path, ant.GetPheromoneAmount());
      UpdateMinPath(min_path, path);
    }
  }

  return min_path;
}

}  // namespace s21
