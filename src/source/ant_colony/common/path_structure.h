#ifndef PARALLELS_SOURCE_ANT_COLONY_COMMON_PATH_STRUCTURE_H
#define PARALLELS_SOURCE_ANT_COLONY_COMMON_PATH_STRUCTURE_H

#include <vector>

namespace s21 {

struct TsmResult {
    std::vector<size_t> vertices;
    double distance;
};

}

#endif  // PARALLELS_SOURCE_ANT_COLONY_COMMON_PATH_STRUCTURE_H


