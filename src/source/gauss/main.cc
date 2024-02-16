#include "gauss/gauss.h"
#include <iostream>

int main() {
  std::vector<std::vector<double>> kMatrix_11_11{{2, 4, 7}, {15, 3, 4}};

  std::vector<double> res = s21::Gauss::SolveAsync(kMatrix_11_11);
  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << res[i] << " ";
  }

  res = s21::Gauss::SolveSync(kMatrix_11_11);
  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << res[i] << " ";
  }

  return 0;
}