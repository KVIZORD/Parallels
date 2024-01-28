#include "ant_colony_async.h"


namespace s21 {

AntColonyAsync::AntColonyAsync(Graph &graph, size_t count_colony, size_t size_colony) : AntColonyBase(graph, count_colony, size_colony) {
}

TsmResult AntColonyAsync::Solve() {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();
  if (graph_.GetSize() == 0) {
    return min_path;
  }

  for (size_t i = 0; i < count_colony_; ++i) {
    size_t ant_count = size_colony_;
    std::vector<std::thread> threads;
    Pheromone pheromones(graph_.GetSize(), kPheromonInitialLevel, kPheromoneEvaporationRate);

    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
      threads.push_back(std::thread([&]() {
          TsmResult path = Task(pheromones, ant_count);
          UpdateMinPath(min_path, path);
      }));
    }

    ThreadWait(threads);
  }

  return min_path;
}

TsmResult AntColonyAsync::Task(Pheromone &pheromones, size_t &ant_count) {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();

  while (true) {
    Ant ant(graph_, gen_, kPheromoneQuantity);

    {
      std::scoped_lock lock(mtx_cnt_);
      if (ant_count == 0) {
        return min_path;
      }
      --ant_count;
    }

    TsmResult path = TravelsAnt(ant, pheromones);

    {
      std::scoped_lock lock(mtx_pheromones_);
      pheromones.Update(path, ant.GetPheromoneAmount());
    }

    UpdateMinPath(min_path, path);
  }

  return min_path;
}

void AntColonyAsync::ThreadWait(std::vector<std::thread> &threads) const {
  for (auto &thread : threads) {
    thread.join();
  }
}

}  // namespace s21
