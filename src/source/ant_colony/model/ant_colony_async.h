#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_ASYNC_H
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_ASYNC_H

#include <vector>
#include <queue>
#include <random>
#include <thread>
#include <mutex>
#include <shared_mutex>


#include "graph.h"
#include "tsm_result.h"
#include "ant.h"
#include "pheromone.h"
#include "ant_colony_base.h"


namespace s21 {

class AntColonyAsync : public AntColonyBase {
public:
    AntColonyAsync(Graph &graph, size_t count_colony, size_t size_colony);
    TsmResult Solve();

private:
    std::mutex mtx_cnt_;
    std::mutex mtx_pheromones_;

    TsmResult Task(Pheromone &pheromones, size_t &ant_count);
    void ThreadWait(std::vector<std::thread> &threads) const;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_ASYNC_H
