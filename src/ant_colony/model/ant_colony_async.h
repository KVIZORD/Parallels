#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_ASYNC_H_
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_ASYNC_H_

#include <mutex>
#include <queue>
#include <random>
#include <shared_mutex>
#include <thread>
#include <vector>

#include "ant_colony/model/ant.h"
#include "ant_colony/model/ant_colony_base.h"
#include "ant_colony/model/graph.h"
#include "ant_colony/model/pheromone.h"
#include "ant_colony/model/tsm_result.h"

namespace s21 {

class AntColonyAsync : public AntColonyBase {
 public:
  AntColonyAsync(Graph &graph, size_t count_colony, size_t size_colony);
  TsmResult Solve() override;

 private:
  std::mutex mtx_cnt_;
  std::mutex mtx_pheromones_;

  TsmResult Task(Pheromone &pheromones, size_t &ant_count);
  void ThreadWait(std::vector<std::thread> &threads) const;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_ASYNC_H_