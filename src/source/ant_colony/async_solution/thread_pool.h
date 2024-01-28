// #ifndef PARALLELS_SOURCE_ANT_COLONY_ASYNC_SOLUTION_THREAD_POOL_H
// #define PARALLELS_SOURCE_ANT_COLONY_ASYNC_SOLUTION_THREAD_POOL_H

// #include <vector>
// #include <thread>


// namespace s21 {

// class ThreadPool {
// public:

//     ThreadPool(size_t count_of_threads) {
//         threads_.reserve(count_of_threads);
//         for (size_t i = 0; i < count_of_threads; ++i) {
//             threads_.push_back(std::thread{&ThreadPool::Run, this});
//         }
//     }


//     ~ThreadPool() {
//         started_ = false;

//         for (auto &thread : threads_) {
//             thread.join();
//         }
//     }

// private:
//     std::vector<std::thread> threads_;
//     std::queue<std::function<void()>> tasks_;
//     std::mutex mtx_;
//     std::condition_variable cv_;
//     std::atomic<bool> started_{true};

//     void Run() {
//         while (started_) {
//             std::unique_lock<std::mutex> lock(mtx_);
//             cv_.wait(lock, [&]() {return !tasks_.empty() || started;});
//             if (!tasks_.empty()) {
//                 auto task = std::move(tasks_.front());
//                 tasks_.pop();
//                 task();
//             }

//         }
//     }

// };

// }

// #endif  // PARALLELS_SOURCE_ANT_COLONY_ASYNC_SOLUTION_THREAD_POOL_H
