#include "common_tests.h"
#include "gauss/model/gauss.h"

namespace s21 {

double kEpsilon = 1e-7;

TEST(GaussSync, Matrix0x0) {
  std::vector<std::vector<double>> matrix = {};

  std::vector<double> result = Gauss().SolveSync(matrix);

  ASSERT_EQ(result.empty(), 1);
}

TEST(GaussSync, Matrix1x2) {
  std::vector<std::vector<double>> matrix = {{1, 5}};

  std::vector<double> result = Gauss().SolveSync(matrix);

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0], 5);
}

TEST(GaussSync, Matrix5x6) {
  std::vector<std::vector<double>> matrix = {{1, 3, 5, 21, 32, 443},
                                             {2, 3, 5, 43, 36, 41},
                                             {3, 6, 5, 21, 62, 44},
                                             {5, 7, 43, 1, 32, 63},
                                             {6, 3, 5, 15, 24, 13}};
  std::vector<double> expected_result = {2213898.0 / 31, -18399805.0 / 31,
                                         1488296.0 / 31, -408830.0 / 31,
                                         1691975.0 / 31};

  std::vector<double> result = Gauss().SolveAsync(matrix);

  ASSERT_EQ(result.size(), expected_result.size());
  for (size_t i = 0; i < expected_result.size(); ++i) {
    ASSERT_NEAR(result[i], expected_result[i], kEpsilon);
  }
}

TEST(GaussSync, NoSoulution) {
  std::vector<std::vector<double>> matrix = {{0, 0, 0, 0, 0, 0},
                                             {2, 0, 5, 43, 36, 41},
                                             {3, 6, 0, 21, 62, 44},
                                             {5, 7, 43, 1, 32, 63},
                                             {6, 3, 5, 15, 24, 13}};

  std::vector<double> result = Gauss().SolveSync(matrix);

  ASSERT_EQ(result.size(), 0);
}

TEST(GaussSync, ZeroesOnMainDiagonal) {
  std::vector<std::vector<double>> matrix = {{0, 3, 5, 21, 32, 443},
                                             {2, 0, 5, 43, 36, 41},
                                             {3, 6, 0, 21, 62, 44},
                                             {5, 7, 43, 0, 32, 63},
                                             {6, 3, 5, 15, 0, 13}};
  std::vector<double> expected_result = {-7985567.0 / 57522, 5002658.0 / 28761,
                                         153761.0 / 95870, 6061319.0 / 287610,
                                         -1586069.0 / 95870};

  std::vector<double> result = Gauss().SolveSync(matrix);

  ASSERT_EQ(result.size(), expected_result.size());
  for (size_t i = 0; i < expected_result.size(); ++i) {
    ASSERT_NEAR(result[i], expected_result[i], kEpsilon);
  }
}

TEST(GaussAsync, Matrix0x0) {
  std::vector<std::vector<double>> matrix = {};

  std::vector<double> result = Gauss().SolveAsync(matrix);

  ASSERT_EQ(result.empty(), 1);
}

TEST(GaussAsync, Matrix1x2) {
  std::vector<std::vector<double>> matrix = {{1, 5}};

  std::vector<double> result = Gauss().SolveAsync(matrix);

  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(result[0], 5);
}

TEST(GaussAsync, Matrix5x6) {
  std::vector<std::vector<double>> matrix = {{1, 3, 5, 21, 32, 443},
                                             {2, 3, 5, 43, 36, 41},
                                             {3, 6, 5, 21, 62, 44},
                                             {5, 7, 43, 1, 32, 63},
                                             {6, 3, 5, 15, 24, 13}};
  std::vector<double> expected_result = {2213898.0 / 31, -18399805.0 / 31,
                                         1488296.0 / 31, -408830.0 / 31,
                                         1691975.0 / 31};

  std::vector<double> result = Gauss().SolveAsync(matrix);

  ASSERT_EQ(result.size(), expected_result.size());
  for (size_t i = 0; i < expected_result.size(); ++i) {
    ASSERT_NEAR(result[i], expected_result[i], kEpsilon);
  }
}

TEST(GaussAsync, NoSoulution) {
  std::vector<std::vector<double>> matrix = {{0, 0, 0, 0, 0, 0},
                                             {2, 0, 5, 43, 36, 41},
                                             {3, 6, 0, 21, 62, 44},
                                             {5, 7, 43, 1, 32, 63},
                                             {6, 3, 5, 15, 24, 13}};

  std::vector<double> result = Gauss().SolveAsync(matrix);

  ASSERT_EQ(result.size(), 0);
}

TEST(GaussAsync, ZeroesOnMainDiagonal) {
  std::vector<std::vector<double>> matrix = {{0, 3, 5, 21, 32, 443},
                                             {2, 0, 5, 43, 36, 41},
                                             {3, 6, 0, 21, 62, 44},
                                             {5, 7, 43, 0, 32, 63},
                                             {6, 3, 5, 15, 0, 13}};
  std::vector<double> expected_result = {-7985567.0 / 57522, 5002658.0 / 28761,
                                         153761.0 / 95870, 6061319.0 / 287610,
                                         -1586069.0 / 95870};

  std::vector<double> result = Gauss().SolveAsync(matrix);

  ASSERT_EQ(result.size(), expected_result.size());
  for (size_t i = 0; i < expected_result.size(); ++i) {
    ASSERT_NEAR(result[i], expected_result[i], kEpsilon);
  }
}

} // namespace s21