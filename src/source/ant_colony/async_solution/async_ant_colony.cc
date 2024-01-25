#include "iostream"

#include "async_ant_colony.h"


namespace s21 {

AsyncAntColony::AsyncAntColony(Graph &graph, size_t count_colony, size_t size_colony)
    : graph_(graph), count_colony_(count_colony), size_colony_(size_colony) {}

TsmResult AsyncAntColony::Solve() {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();
  if (graph_.GetSize() == 0) {
    return min_path;
  }

  for (size_t i = 0; i < count_colony_; ++i) {
    Pheromone pheromones(graph_.GetSize(), kPheromonInitialLevel, kPheromoneEvaporationRate);
    CreateAntColony();

    for (auto &ant : ant_colony) {
        while (ant.Move(pheromones)) {
        }

        const TsmResult &path = ant.GetPath();
        pheromones.Update(path, ant.GetPheromoneAmount());

        if (path.vertices.size() == (graph_.GetSize() + 1) &&
            path.distance < min_path.distance) {
            min_path = std::move(path);
        }
    }
  }

  return min_path;
}

void AsyncAntColony::CreateAntColony() {
    ant_colony.clear();
    ant_colony.reserve(size_colony_);
    for (size_t i = 0; i < size_colony_; ++i) {
        ant_colony.push_back(Ant(graph_, gen_, kPheromoneQuantiy));
    }
}

}  // namespace s21
