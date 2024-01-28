#ifndef PARALLELS_SOURCE_ANT_COLONY_COMMON_ANT_COLONY_H
#define PARALLELS_SOURCE_ANT_COLONY_COMMON_ANT_COLONY_H

#include <vector>
#include <random>

#include "../common/graph.h"
#include "../common/path_structure.h"
#include "../common/ant.h"
#include "../common/pheromone.h"

namespace s21 {

class AntColony {
public:
    virtual TsmResult Solve() = 0;
};

}

#endif  // PARALLELS_SOURCE_ANT_COLONY_COMMON_ANT_COLONY_H
