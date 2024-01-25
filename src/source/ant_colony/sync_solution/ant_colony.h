#ifndef PARALLELS_SOURCE_ANT_COLONY_SYNC_SOLUTION_ANT_COLONY_H
#define PARALLELS_SOURCE_ANT_COLONY_SYNC_SOLUTION_ANT_COLONY_H

#include <vector>
#include <random>

#include "../common/graph.h"
#include "../common/path_structure.h"
#include "../common/ant.h"
#include "../common/pheromone.h"

namespace s21 {

class AntColony {
public:
    const double kPheromoneQuantiy = 15.0;
    const double kPheromoneEvaporationRate = 0.1;
    const double kPheromonInitialLevel = 1;

    AntColony(Graph &graph, size_t count_colony, size_t size_colony);
    TsmResult Solve();

private:
    Graph &graph_;
    size_t count_colony_;
    size_t size_colony_;
    std::vector<Ant> ant_colony{};
    std::random_device rd_{};
    std::mt19937 gen_{rd_()};

    void CreateAntColony();

};

}

#endif  // PARALLELS_SOURCE_ANT_COLONY_SYNC_SOLUTION_ANT_COLONY_H
