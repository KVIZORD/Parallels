#include "pheromone.h"


namespace s21 {

Pheromone::Pheromone(size_t size, double init_pheromone, double evaporation_rate) 
    : pheromone_matrix_(std::vector<std::vector<double>>(size, std::vector<double>(init_pheromone))), evaporation_rate_(evaporation_rate) {
    for (size_t i = 0; i < size; i++) {
        pheromone_matrix_[i][i] = 0;
    }
}

double Pheromone::GetValue(size_t from, size_t to) const {
    return pheromone_matrix_[from][to];
}

void Pheromone::Update(const TsmResult &path, double pheromon_amount) {
    double average_pheromone = pheromon_amount / path.distance;
    Evapration();
    Lay(path.path, average_pheromone);
}

void Pheromone::Evapration() {
    for (size_t i = 0; i < pheromone_matrix_.size(); ++i) {
        for (size_t j = 0; j < pheromone_matrix_.size(); ++j) {
            pheromone_matrix_[i][j] *= (1 - evaporation_rate_);
        }
    }
}

void Pheromone::Lay(const std:vector<size_t> &path, double average_pheromone) {
    for (size_t i = 0; (i + 1) < path.size(); ++i) {
        size_t from = path[i];
        size_t to = path[i + 1];
        pheromone_matrix_[from][to] += average_pheromone;
        pheromone_matrix_[to][from] += average_pheromone;
    }
}

}  // namespace s21