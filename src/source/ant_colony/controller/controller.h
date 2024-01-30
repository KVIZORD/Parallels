#ifndef PARALLELS_SOURCE_ANT_COLONY_CONTROLLER_CONTROLLER_H
#define PARALLELS_SOURCE_ANT_COLONY_CONTROLLER_CONTROLLER_H

#include "ant_colony/model/ant_colony_async.h"
#include "ant_colony/model/ant_colony_base.h"
#include "ant_colony/model/ant_colony_sync.h"
#include "ant_colony/model/graph.h"
#include "ant_colony/model/tsm_result.h"

namespace s21 {

class Controller {
 public:
  using Matrix = std::vector<std::vector<size_t>>;

  Controller(Graph &graph, AntColonySync &ant_colony_sync,
             AntColonyAsync &ant_colony_async);

  void UpdateGraph(Matrix &&matrix);
  bool IsEmptyGraph() const;
  TsmResult SolveSyncTsm();
  TsmResult SolveAsyncTsm();

 private:
  Graph &graph_;
  AntColonySync &ant_colony_sync_;
  AntColonyAsync &ant_colony_async_;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_CONTROLLER_CONTROLLER_H
