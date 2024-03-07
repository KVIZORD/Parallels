#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_TSM_RESULT_H_
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_TSM_RESULT_H_

#include <cstddef>
#include <vector>

namespace s21 {

struct TsmResult {
  std::vector<size_t> vertices;
  double distance;
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_TSM_RESULT_H_