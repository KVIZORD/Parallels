#ifndef PARALLELS_SOURCE_ANT_COLONY_MODEL_PHEROMONE_H
#define PARALLELS_SOURCE_ANT_COLONY_MODEL_PHEROMONE_H

#include <cstddef>
#include <iostream>
#include <vector>

#include "tsm_result.h"

namespace s21 {

class Pheromone {
 public:
  Pheromone(size_t size, double init_pheromone, double evaporation_rate);
  double GetValue(size_t from, size_t to) const;
  void Update(const TsmResult &path, double pheromone_amount);

  void Print() const;

 private:
  std::vector<std::vector<double>> pheromone_matrix_;
  double evaporation_rate_;

  void Evapration();
  void Lay(const std::vector<size_t> &path_vertices, double average_pheromone);
};

}  // namespace s21

#endif  // PARALLELS_SOURCE_ANT_COLONY_MODEL_PHEROMONE_H