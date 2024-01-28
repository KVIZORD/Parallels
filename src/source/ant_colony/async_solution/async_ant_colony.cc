#include "iostream"

#include "async_ant_colony.h"


namespace s21 {

AntColonyAsync::AntColonyAsync(Graph &graph, size_t count_colony, size_t size_colony) : graph_(graph), count_colony_(count_colony), size_colony_(size_colony) {
}

AntColonyAsync::~AntColonyAsync() {
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
          TsmResult path = Task(pheromones, ant_count, mutex_, graph_, gen_, kPheromoneQuantity);
          UpdateMinPath(min_path, path);
      }));
    }

    ThreadWait(threads);
  }

  return min_path;
}

void AntColonyAsync::UpdateMinPath(TsmResult &min_path, TsmResult &path) const {
  if (path.vertices.size() == (graph_.GetSize() + 1) && path.distance < min_path.distance) {
    min_path = std::move(path);
  }
}

void AntColonyAsync::ThreadWait(std::vector<std::thread> &threads) const {
  for (auto &thread : threads) {
    thread.join();
  }
}

TsmResult AntColonyAsync::Task(Pheromone &pheromones, size_t &ant_count, std::mutex &mtx, Graph &graph, std::mt19937 &gen, double kPheromoneQuantity) {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();

  while (true) {
    Ant ant(graph, gen, kPheromoneQuantity);

    {
      std::scoped_lock lg(mtx);
      if (ant_count == 0) {
        return min_path;
      }
      --ant_count;
    }

    // std::shared_mutex lock(mtx);
    while (ant.Move(pheromones)) {
    }

    const TsmResult &path = ant.GetPath();

  {
    std::scoped_lock lg(mtx);
    pheromones.Update(path, ant.GetPheromoneAmount());
  }

    if (path.vertices.size() == (graph_.GetSize() + 1) &&
        path.distance < min_path.distance) {
        min_path = std::move(path);
    }
  }

  return min_path;
}

}  // namespace s21
