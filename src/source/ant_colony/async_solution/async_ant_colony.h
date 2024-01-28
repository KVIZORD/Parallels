#ifndef PARALLELS_SOURCE_ANT_COLONY_ASYNC_SOLUTION_ASYNC_ANT_COLONY_H
#define PARALLELS_SOURCE_ANT_COLONY_ASYNC_SOLUTION_ASYNC_ANT_COLONY_H

#include <vector>
#include <queue>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>


#include "../common/graph.h"
#include "../common/path_structure.h"
#include "../common/ant.h"
#include "../common/pheromone.h"

namespace s21 {

class AntColonyAsync {
public:
    const double kPheromoneQuantity = 15.0;
    const double kPheromoneEvaporationRate = 0.1;
    const double kPheromonInitialLevel = 1;

    AntColonyAsync(Graph &graph, size_t count_colony, size_t size_colony);
    ~AntColonyAsync();
    TsmResult Solve();
    

private:
    Graph &graph_;
    size_t count_colony_;
    size_t size_colony_;
    std::vector<Ant> ant_colony{};
    std::queue<Ant> ant_queue{};
    std::random_device rd_{};
    std::mt19937 gen_{rd_()};
    // Pheromone &pheromone_;
    // Pheromone pheromones_;
    // TsmResult min_path;


    // std::vector<std::thread> threads_;
    std::mutex mutex_;
    // std::mutex mutex_pheromones_;
    // std::mutex mutex_queue_;
    // std::condition_variable cv_;
    // std::atomic<bool> started_{true};

    // void CreateAntColony();
    // void Run();
    // void Task(Ant &ant, Pheromone &pheromones, TsmResult &min_path);
    TsmResult Task(Pheromone &pheromones, size_t &ant_count, std::mutex &mtx, Graph &graph, std::mt19937 &gen, double kPheromoneQuantity);

    
};

}

#endif  // PARALLELS_SOURCE_ANT_COLONY_ASYNC_SOLUTION_ASYNC_ANT_COLONY_H
