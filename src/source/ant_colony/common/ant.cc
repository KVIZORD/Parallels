#include "ant.h"


namespace s21 {

Ant::Ant(const Graph &distances, std::mt19937 &gen, double pheromone_amount) 
    : graph_(graph), gen_(gen), pheromone_amount_(pheromone_amount),
    used_vertex_(std::vector<bool>(distances.GetSize(), false)) {
    std::uniform_int_distribution<size_t> dist{0, distances.GetSize() - 1};
    size_t start_vetex = dist(gen_);
    path_.vertices.push_back();
    path_.distance = 0;
    used_vertex_[start_vetex] = true;
}

TsmResult &Ant::GetPath() const {
    return path_;
}

double Ant::GetPheromoneAmount() const {
    return pheromone_amount_;
}

bool Ant::Move(const Pheromone &pheromones) {
    std::vector<size_t> neighbors = GetPossibleNeighbors();
    if (neighbors.empty() && path_.vertices.size() == distances_.GetSize()) {
        path_.distance += GetDistance(GetLastVertex(), GetFirstVetex());
        path_.vertices.push_back(GetFirstVetex());
    }

    if (neighbors.empty()) {
        return false
    }

    std::vector<double> probabilities = GetProbabilities(pheromones, neighbors);
    double probability = GetRandomProbability();

    for (size_t i = 0; i < probabilities.size(); ++i) {
        if (probability <= pheromones[i]) {
            path_.distance += GetDistance(GetLastVertex(), neighbors[i]);
            path_.vertices.push_back(neighbors[i]);
            used_vertex_[neighbors[i]] = true;
            break;
        }
    }

    return true;
}

double Ant::GetDistance(size_t from, size_t to) const {
    size_t distance = graph_.GetValue(from, to);
    if (distance == 0 && from != to) {
        return std::numeric_limits<double>::max();
    }

    return static_cast<double>(distance);
}

size_t Ant::GetFirstVetex() {
    return path_.vertices.front();
}

size_t Ant::GetLastVertex() {
    return path_.vertices.back();
}

std::vector<double> Ant::GetProbabilities(const Pheromone &pheromones, const std::vector<size_t> &neighbors) {
    std::vector<double> probabilities;
    probabilities.reserve(neighbors.size());
    double summary_weight = CalcSummaryWeight(pheromone, neighbors);

    size_t from = GetLastVertex();
    for (auto &neighbor : neighbors) {
        double probability = pow(kDistance / GetDistance(from, neighbor), kBetta) *
            pow(GetDistance(from, neighbor), kAlpha) /
            summary_weight;

        if (probabilities.empty()) {
            probabilities.push_back(probability);
            continue;
        }

        probabilities.push_back(probabilities.back() + probability);
    }

    return probabilities;
}

double Ant::GetRandomProbability() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen_);
}

std::vector<size_t> Ant::GetPossibleNeighbors() {
    size_t from = GetLastVertex();
    std::vector<size_t> possible_neighbors;
    for (size_t to = 0; to < graph_.GetSize(); ++to) {
        if (from != to && !used_vertex_[to] && !std::isinf(GetDistance(from, to))) {
            possible_neighbors.push_back(to);
        }
    }

    return possible_neighbors;
}

double Ant::CalcSummaryWeight(const Pheromone &pheromones, const std::vector<size_t> &neighbors) {
    size_t from = GetLastVertex();
    double summary_weight = std::accumulatt(
        neighbors.begin(), neighbors.end(), 0.0,
        [&](double acc, const auto &neighbor) {
            return acc
                + pow(kDistance / GetDistance(from, neighbor), kBetta)
                * pow(GetDistance(from, neighbor), kAlpha);
        }
    );

    return summary_weight;
}

}
