
#include <vector>
#include <iostream>

#include "model/ant_colony_async.h"
#include "model/ant_colony_sync.h"
#include "model/graph.h"
#include "model/tsm_result.h"

#include "view/view.h"
#include "controller/controller.h"
#include "model/ant_colony_base.h"
#include "model/ant_colony_sync.h"
#include "model/ant_colony_async.h"


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


// int main() {
//     std::vector<std::vector<size_t>> matrix = {
//         {0,   29,  20,  21,  16,  31,  100, 12,  4,   31,  18},
//         {29,  0,   15,  29,  28,  40,  72,  21,  29,  41,  12},
//         {20,  15,  0,   15,  14,  25,  81,  9,   23,  27,  13},
//         {21,  29,  15,  0,   4,   12,  92,  12,  25,  13,  25},
//         {16,  28,  14,  4,   0,   16,  94,  9,   20,  16,  22},
//         {31,  40,  25,  12,  16,  0,   95,  24,  36,  3,   37},
//         {100, 72,  81,  92,  94,  95,  0,   90,  101, 99,  84},
//         {12,  21,  9,   12,  9,   24,  90,  0,   15,  25,  13},
//         {4,   29,  23,  25,  20,  36,  101, 15,  0,   35,  18},
//         {31,  41,  27,  13,  16,  3,   99,  25,  35,  0,   38},
//         {18,  12,  13,  25,  22,  37,  84,  13,  18,  38,  0}
//     };

//     s21::Graph graph(matrix);

//     s21::AntColonySync colony(graph, 1, 200000);
//     s21::TsmResult res = colony.Solve();
//     std::cout << res.distance << std::endl;

//     s21::AntColonyAsync colony_async(graph, 1, 200000);
//     s21::TsmResult res_async = colony_async.Solve();
//     std::cout << res_async.distance << std::endl;

//     std::cout << "Hello World!" << std::endl;
//     return 0;
// }
