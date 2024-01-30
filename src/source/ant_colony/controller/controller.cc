#include "controller.h"

namespace s21 {

Controller::Controller(Graph &graph, AntColonySync &ant_colony_sync,
                       AntColonyAsync &ant_colony_async)
    : graph_(graph),
      ant_colony_sync_(ant_colony_sync),
      ant_colony_async_(ant_colony_async) {}

void Controller::UpdateGraph(Matrix &&matrix) {
  graph_.SetMatrix(std::move(matrix));
}

bool Controller::IsEmptyGraph() const { return graph_.GetSize() == 0; }

TsmResult Controller::SolveSyncTsm() { return ant_colony_sync_.Solve(); }

TsmResult Controller::SolveAsyncTsm() { return ant_colony_async_.Solve(); }

}  // namespace s21
