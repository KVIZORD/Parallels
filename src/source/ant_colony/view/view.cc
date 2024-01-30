#include "view.h"

namespace s21 {

View::View(Controller &controller) : controller_(controller) {}

void View::Exec() {
  while (true) {
    ShowMenu();
    long long action = ReadNumber();
    switch (action) {
      case 1:
        LoadGraphFromConsole();
        break;
      case 2:
        LoadGraphFromFile();
        break;
      case 3:
        OutputSolutionTsm();
        break;
      case 4:
        CompareSolutionsTsm();
        break;
      case 5:
        return;
      default:
        std::cout << "\033[1;31mWrong command. Try again.\033[0m" << std::endl;
        break;
    }
  }
}

void View::CompareSolutionsTsm() {
  if (controller_.IsEmptyGraph()) {
    std::cout << "\033[1;31mThe graph is empty.\033[0m" << std::endl;
    return;
  }

  std::cout << "Input the number of repetitions:" << std::endl;
  long long count = ReadNumber();
  if (count < 0) {
    std::cout << "\033[1;31mWrong number of repetitions.\033[0m" << std::endl;
    return;
  }

  std::chrono::milliseconds time_sync =
      MeasureTime([&]() { return RunMultiple(count, TsmSolveMethod::kSync); });
  std::chrono::milliseconds time_async =
      MeasureTime([&]() { return RunMultiple(count, TsmSolveMethod::kAsync); });

  std::cout << "Times of execution: " << std::endl;
  std::cout << "\t- synchronously:  " << time_sync.count() << "ms" << std::endl;
  std::cout << "\t- asynchronously: " << time_async.count() << "ms"
            << std::endl;
}

void View::OutputSolutionTsm() {
  if (controller_.IsEmptyGraph()) {
    std::cout << "\033[1;31mThe graph is empty.\033[0m" << std::endl;
    return;
  }

  std::cout << "Input the number of repetitions:" << std::endl;
  long long count = ReadNumber();
  if (count < 0) {
    std::cout << "\033[1;31mWrong number of repetitions.\033[0m" << std::endl;
    return;
  }

  TsmResult pathSync = RunMultiple(count, TsmSolveMethod::kSync);
  TsmResult pathAsync = RunMultiple(count, TsmSolveMethod::kAsync);

  PrintPathResult(pathSync, pathAsync);
}

void View::PrintPathResult(const TsmResult &path_sync, const TsmResult &path_async) {
  std::cout << "Shortest path: " << std::endl;  
  
  std::cout << "\t- synchronously:  ";
  if (std::isinf(path_sync.distance)) {
    std::cout << "not found solution" << std::endl;
  } else {
    std::cout << path_sync.distance << std::endl;
  }

  std::cout << "\t- asynchronously: ";
  if (std::isinf(path_async.distance)) {
    std::cout << "not found solution" << std::endl;
  } else {
    std::cout << path_async.distance << std::endl;
  }
}

TsmResult View::RunMultiple(size_t count, TsmSolveMethod method) {
  TsmResult min_path;
  min_path.distance = std::numeric_limits<double>::infinity();
  for (size_t i = 0; i < count; i++) {
    TsmResult path = (method == kSync) ? controller_.SolveSyncTsm()
                                       : controller_.SolveAsyncTsm();
    if (path.distance < min_path.distance) {
      min_path = std::move(path);
    }
  }

  return min_path;
}

void View::ShowMenu() {
  std::cout << "Select an option: " << std::endl;
  std::cout
      << "------------------------------------------------------------------"
      << std::endl;
  std::cout << "1. Load graph from console" << std::endl;
  std::cout << "2. Load graph from file" << std::endl;
  std::cout << "3. Solve the traveling salesman problem" << std::endl;
  std::cout
      << "4. Compare time versions of solving the traveling salesman problem"
      << std::endl;
  std::cout << "5. Exit" << std::endl;
  std::cout
      << "------------------------------------------------------------------"
      << std::endl;
}

void View::LoadGraphFromConsole() {
  std::cout << "Input size of graph: ";
  long long size = ReadNumber();
  if (size <= 0) {
    std::cout << "\033[1;31mWrong size.\033[0m" << std::endl;
    return;
  }

  std::cout << "Input matrix of graph: " << std::endl;
  try {
    Matrix matrix = ReadMatrix(size);
    controller_.UpdateGraph(std::move(matrix));
  } catch (std::invalid_argument &e) {
    std::cout << "\033[1;31mIncorrect matrix. \033[0m" << std::endl;
    return;
  }
}

void View::LoadGraphFromFile() {
  std::cout << "Input file path: ";
  std::string f_name = ReadLine();

  std::ifstream in;
  in.open(f_name);

  if (!in.is_open()) {
    std::cout << "\033[1;31mFile not found.\033[0m" << std::endl;
    return;
  }

  long long size = ReadNumber(in);
  if (size <= 0) {
    std::cout << "\033[1;31mWrong size.\033[0m" << std::endl;
    return;
  }

  try {
    Matrix matrix = ReadMatrix(size, in);
    controller_.UpdateGraph(std::move(matrix));
  } catch (std::invalid_argument &e) {
    std::cout << "\033[1;31mIncorrect matrix. \033[0m" << std::endl;
    return;
  }
}

View::Matrix View::ReadMatrix(size_t size, std::istream &in) {
  Matrix matrix(size, std::vector<size_t>(size, 0));
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      long long value = ReadNumber(in);
      if (value < 0) {
        throw std::invalid_argument("Incorrect matrix.");
      }
      matrix[i][j] = static_cast<size_t>(value);
    }
  }
  return matrix;
}

long long View::ReadNumber(std::istream &in) {
  long long number{};
  in >> number;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    number = -1;
  }
  return number;
}

std::string View::ReadLine(std::istream &in) {
  std::string f_name;
  in >> f_name;
  return f_name;
}

std::chrono::milliseconds View::MeasureTime(
    std::function<TsmResult()> solve_tsm) {
  auto begin = std::chrono::steady_clock::now();

  solve_tsm();

  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

}  // namespace s21
