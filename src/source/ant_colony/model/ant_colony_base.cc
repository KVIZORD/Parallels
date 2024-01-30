#include "ant_colony_base.h"

namespace s21 {

AntColonyBase::AntColonyBase(Graph &graph, size_t count_colony,
                             size_t size_colony)
    : graph_(graph), count_colony_(count_colony), size_colony_(size_colony) {}

TsmResult AntColonyBase::TravelsAnt(Ant &ant, Pheromone &pheromones) {
  while (ant.Move(pheromones)) {
  }

  TsmResult path = std::move(ant.GetPath());

  return path;
}

void AntColonyBase::UpdateMinPath(TsmResult &min_path,
                                  const TsmResult &path) const {
  if (path.vertices.size() == (graph_.GetSize() + 1) &&
      path.distance < min_path.distance) {
    min_path = std::move(path);
  }
}

}  // namespace s21
