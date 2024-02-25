
#include <iostream>
#include <vector>

#include "ant_colony/controller/controller.h"
#include "ant_colony/model/ant_colony_async.h"
#include "ant_colony/model/ant_colony_base.h"
#include "ant_colony/model/ant_colony_sync.h"
#include "ant_colony/model/graph.h"
#include "ant_colony/model/tsm_result.h"
#include "ant_colony/view/view.h"

int main() {
  size_t count_colony = 1;
  size_t size_colony = 100;
  s21::Graph graph;
  s21::AntColonySync ant_colony_sync(graph, count_colony, size_colony);
  s21::AntColonyAsync ant_colony_async(graph, count_colony, size_colony);

  s21::Controller controller(graph, ant_colony_sync, ant_colony_async);
  s21::View view(controller);
  view.Exec();
}
