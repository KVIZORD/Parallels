#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_SYNC_H
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_SYNC_H

#include <vector>
#include <random>

#include "graph.h"
#include "tsm_result.h"
#include "ant.h"
#include "pheromone.h"
#include "ant_colony_base.h"


namespace s21 {

class AntColonySync : public AntColonyBase {
public:
    AntColonySync(Graph &graph, size_t count_colony, size_t size_colony);
    TsmResult Solve();
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_ANT_COLONY_SYNC_H
