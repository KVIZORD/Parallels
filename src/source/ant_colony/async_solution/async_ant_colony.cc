#include "iostream"

#include "async_ant_colony.h"


namespace s21 {

AntColonyAsync::AntColonyAsync(Graph &graph, size_t count_colony, size_t size_colony) : graph_(graph), count_colony_(count_colony), size_colony_(size_colony) {
  // } // size_t thread_count = std::thread::hardware_concurrency();
  // threads_.reserve(thread_count);
  // for (size_t i = 0; i < thread_count; ++i) {
  //     threads_.push_back(std::thread{&AntColonyAsync::Run, this});
 
}

AntColonyAsync::~AntColonyAsync() {
  // {
  //   std::unique_lock<std::mutex> lock(mutex_);
  //   started_ = false;
  // }
  // cv_.notify_all();
  // std::cout << "Count of threads: " << threads_.size() << std::endl;
  // for (auto &thread : threads_) {
  //     std::cout << "Thread Stopped" << std::endl;
  //     thread.join();
  // }
}

TsmResult AntColonyAsync::Solve() {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();

  if (graph_.GetSize() == 0) {
    return min_path;
  }

  for (size_t i = 0; i < count_colony_; ++i) {
    size_t ant_count = size_colony_;

    // std::vector<std::future<TsmResult>> futures;
    std::vector<std::thread> threads;
    Pheromone pheromones(graph_.GetSize(), kPheromonInitialLevel, kPheromoneEvaporationRate);
    
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
      threads.push_back(
        std::thread([&]() {
          TsmResult path = Task(pheromones, ant_count, mutex_, graph_, gen_, kPheromoneQuantity);
          if (path.vertices.size() == (graph_.GetSize() + 1) && path.distance < min_path.distance) {
            min_path = std::move(path);
          }
        })
      );
      // threads.push_back(
      //   std::thread(&AntColonyAsync::Task, this, std::ref(pheromones), std::ref(ant_count), std::ref(mutex_), std::ref(graph_), std::ref(gen_), kPheromoneQuantity)
      // );
      // futures.push_back(std::async(std::launch::async, &AntColonyAsync::Task, this, std::ref(pheromones), std::ref(ant_count), std::ref(mutex_), std::ref(graph_), std::ref(gen_), kPheromoneQuantity));
    }
    for (auto &thread : threads) {
      thread.join();
    }
    // for (auto &future : futures) {
    //   TsmResult path = future.get();
    //   if (path.vertices.size() == (graph_.GetSize() + 1) && path.distance < min_path.distance) {
    //     min_path = std::move(path);
    //   }
    // }

  }

  return min_path;
}

TsmResult AntColonyAsync::Task(Pheromone &pheromones, size_t &ant_count, std::mutex &mtx, Graph &graph, std::mt19937 &gen, double kPheromoneQuantity) {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();

  while (true) {
    Ant ant(graph, gen, kPheromoneQuantity);

    {
      std::scoped_lock lg(mtx);
      if (ant_count == 0) {
        return min_path;
      }
      --ant_count;
    }


    // Здесь блокировка на чтение
    while (ant.Move(pheromones)) {
    }

    const TsmResult &path = ant.GetPath();
    // std::cout << path.distance << std::endl;

  {
    // Здесь блокировка на запись
    std::scoped_lock lg(mtx);
    pheromones.Update(path, ant.GetPheromoneAmount());
  }

    // Здесь блоировка на запись пути
    if (path.vertices.size() == (graph_.GetSize() + 1) &&
        path.distance < min_path.distance) {
        min_path = std::move(path);
    }
  }

  return min_path;
}

// void AntColonyAsync::Task(Ant &ant, Pheromone &pheromones_, TsmResult &min_path) {
//   TsmResult min_path;
//   min_path.distance = std::numeric_limits<double>::infinity();

//   // Здесь блокировка на чтение
//   while (ant.Move(pheromones_)) {
//   }

//   const TsmResult &path = ant.GetPath();
//   // std::cout << path.distance << std::endl;

//   // Здесь блокировка на запись
//   pheromones_.Update(path, ant.GetPheromoneAmount());

//   // Здесь блоировка на запись пути
//   if (path.vertices.size() == (graph_.GetSize() + 1) &&
//       path.distance < min_path.distance) {
//       min_path = std::move(path);
//   }
//   // return min_path;
// }

// void AntColonyAsync::CreateAntColony() {
//     for (size_t i = 0; i < size_colony_; ++i) {
//         // std::scoped_lock lg(mutex_queue_);
//         ant_colony.push_back(Ant(graph_, gen_, kPheromoneQuantity));
//         // ant_queue.push(Ant(graph_, gen_, kPheromoneQuantity));
//         // cv_.notify_one();
//     }
// }

  // void AntColonyAsync::Run() {
  //   // std::cout << "Thread is running" << std::endl;
  //     while (started_) {
  //         std::unique_lock<std::mutex> lock(mutex_);
  //         cv_.wait(lock, [&]() {return !ant_queue.empty() && started_;});
  //         std::cout << "started_ = " << started_ << std::endl;
  //         if (!ant_queue.empty()) {
  //             auto ant = std::move(ant_queue.front());
  //             ant_queue.pop();
  //             Task(ant, pheromones_, min_path);
  //         }
  //         cv_.notify_one();
  //     }
  // }

}  // namespace s21
