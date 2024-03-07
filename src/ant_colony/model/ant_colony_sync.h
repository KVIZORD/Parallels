#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_SYNC_H_
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_SYNC_H_

#include <random>
#include <vector>

#include "ant_colony/model/ant.h"
#include "ant_colony/model/ant_colony_base.h"
#include "ant_colony/model/graph.h"
#include "ant_colony/model/pheromone.h"
#include "ant_colony/model/tsm_result.h"

namespace s21 {

class AntColonySync : public AntColonyBase {
 public:
  AntColonySync(Graph &graph, size_t count_colony, size_t size_colony);
  TsmResult Solve() override;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_SYNC_H_