#include "common_tests.h"
#include "../source/ant_colony/model/graph.h"
#include "../source/ant_colony/model/ant_colony_sync.h"
#include "../source/ant_colony/model/ant_colony_async.h"


std::vector<std::vector<size_t>> kMatrix_0_0{};
std::vector<std::vector<size_t>> kMatrix_1_1{{0}};
std::vector<std::vector<size_t>> kMatrix_2_2{
  {0, 2},
  {2, 0}
};
std::vector<std::vector<size_t>> kMatrix_3_2{
  {0, 2},
  {2, 0},
  {1, 5}
};
std::vector<std::vector<size_t>> kMatrix_2_3{
  {0, 2, 3},
  {2, 0, 4},
};
std::vector<std::vector<size_t>> kMatrix_11_11{
  {0,   29,  20,  21,  16,  31,  100, 12,  4,   31,  18},
  {29,  0,   15,  29,  28,  40,  72,  21,  29,  41,  12},
  {20,  15,  0,   15,  14,  25,  81,  9,   23,  27,  13},
  {21,  29,  15,  0,   4,   12,  92,  12,  25,  13,  25},
  {16,  28,  14,  4,   0,   16,  94,  9,   20,  16,  22},
  {31,  40,  25,  12,  16,  0,   95,  24,  36,  3,   37},
  {100, 72,  81,  92,  94,  95,  0,   90,  101, 99,  84},
  {12,  21,  9,   12,  9,   24,  90,  0,   15,  25,  13},
  {4,   29,  23,  25,  20,  36,  101, 15,  0,   35,  18},
  {31,  41,  27,  13,  16,  3,   99,  25,  35,  0,   38},
  {18,  12,  13,  25,  22,  37,  84,  13,  18,  38,  0}
};
std::vector<std::vector<size_t>> kMatrixNoSolution{
  {0,   29,  20,  21,  16,  1,   100, 12,  4,   31,  18},
  {29,  0,   15,  29,  28,  0,   72,  21,  29,  41,  12},
  {20,  15,  0,   15,  14,  0,   81,  9,   23,  27,  13},
  {21,  29,  15,  0,   4,   0,   92,  12,  25,  13,  25},
  {16,  28,  14,  4,   0,   0,   94,  9,   20,  16,  22},
  {1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
  {100, 72,  81,  92,  94,  0,   0,   90,  101, 99,  84},
  {12,  21,  9,   12,  9,   0,   90,  0,   15,  25,  13},
  {4,   29,  23,  25,  20,  0,   101, 15,  0,   35,  18},
  {31,  41,  27,  13,  16,  0,   99,  25,  35,  0,   38},
  {18,  12,  13,  25,  22,  0,   84,  13,  18,  38,  0}
};

static const size_t count_colony = 1;
static const size_t size_colony = 1000;
// s21::AntColonySync ant_colony_sync(graph, count_colony, size_colony);
// s21::AntColonyAsync ant_colony_async(graph, count_colony, size_colony);

// TEST(AntColonySyncTest, ThrowEmptyGraph) {
//   ASSERT_THROW(s21::Graph graph(kMatrix_0_0), std::invalid_argument);
//   // s21::AntColonySync ant_colony(graph, count_colony, size_colony);
//   // ASSERT_EQ(ant_colony.Solve().distance, std::numeric_limits<double>::infinity());
// }


TEST(AntColonySyncTest, SingleVertexGraph) {
  s21::Graph graph(kMatrix_1_1);
  s21::AntColonySync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_EQ(result.distance, 0);
}

TEST(AntColonySyncTest, TwoVertexGraph) {
  s21::Graph graph(kMatrix_2_2);
  s21::AntColonySync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_EQ(result.distance, 4);

}

TEST(AntColonySyncTest, NotSquareGraph) {
  ASSERT_THROW(s21::Graph graph(kMatrix_3_2), std::invalid_argument);
}

TEST(AntColonySyncTest, SetNotSquareGraph) {
  s21::Graph graph;
  ASSERT_THROW(graph.SetMatrix(std::move(kMatrix_2_3)), std::invalid_argument);
}

TEST(AntColonySyncTest, NoSolutionGraph) {
  s21::Graph graph(kMatrixNoSolution);
  s21::AntColonySync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.distance, std::numeric_limits<double>::infinity());
}

TEST(AntColonySyncTest, LargeGraph) {
  s21::Graph graph(kMatrix_11_11);
  s21::AntColonySync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_LT(result.distance, 270);
  ASSERT_GT(result.distance, 250);
}

// TEST(AntColonySyncTest, MultipleRunsGraphNoCheckLeaks) {
//   s21::Graph graph(kMatrix_11_11);
//   s21::AntColonySync ant_colony(graph, count_colony, size_colony);
  

//   for (size_t i = 0; i < 50; ++i) {
//     s21::TsmResult result = ant_colony.Solve();
//     ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
//     ASSERT_LT(result.distance, 270);
//     ASSERT_GT(result.distance, 250);
//   }
// }



TEST(AntColonyAyncTest, SingleVertexGraph) {
  s21::Graph graph(kMatrix_1_1);
  s21::AntColonyAsync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_EQ(result.distance, 0);
}

TEST(AntColonyAsyncTest, TwoVertexGraph) {
  s21::Graph graph(std::move(kMatrix_2_2));
  s21::AntColonyAsync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_EQ(result.distance, 4);
}

TEST(AntColonyAsyncTest, NotSquareGraph) {
  ASSERT_THROW(s21::Graph graph(std::move(kMatrix_3_2)), std::invalid_argument);
}

TEST(AntColonyAsyncTest, NoSolutionGraph) {
  s21::Graph graph(kMatrixNoSolution);
  s21::AntColonyAsync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.distance, std::numeric_limits<double>::infinity());
}

TEST(AntColonyAsyncTest, LargeGraph) {
  s21::Graph graph;
  graph.SetMatrix(std::move(kMatrix_11_11));
  s21::AntColonyAsync ant_colony(graph, count_colony, size_colony);
  s21::TsmResult result = ant_colony.Solve();

  ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
  ASSERT_LT(result.distance, 270);
  ASSERT_GT(result.distance, 250);
}

// TEST(AntColonyAsyncTest, MultipleRunsGraphNoCheck_Leaks) {
//   s21::Graph graph(kMatrix_11_11);
//   s21::AntColonyAsync ant_colony(graph, count_colony, size_colony);
  

//   for (size_t i = 0; i < 10; ++i) {
//     s21::TsmResult result = ant_colony.Solve();
//     ASSERT_EQ(result.vertices.size(), graph.GetSize() + 1);
//     ASSERT_LT(result.distance, 270);
//     ASSERT_GT(result.distance, 250);
//   }
// }
