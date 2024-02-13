#include "s21_view.h"

namespace s21 {
View::~View() {
  if (controller_) {
    delete controller_;
  }
}

void View::Run() {
  try {
    FillMatrix();
    int iter = CheckCorrectNumberInput("Input number of iteration: ");

    std::function<Matrix()> operation = [this]() {
      return controller_->MulMatrix();
    };
    PrintMulMatrix("Simple multiply", iter, operation);

    operation = [this]() { return controller_->MulMatrixWinograd(); };
    PrintMulMatrix("Winograd multiply", iter, operation);

    auto operation1 = [this](size_t threads) {
      return controller_->MulMatrixParallelWinograd(threads);
    };
    PrintMulMatrixParallel("Winograd parallel multiply", iter, operation1);

    operation = [this]() { return controller_->MulMatrixConveyorWinograd(); };
    PrintMulMatrix("Winograd conveyor parallel multiply", iter, operation);
  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}

void View::PrintDataMatrix() {
  auto first_matrix = controller_->GetData().a;
  auto second_matrix = controller_->GetData().b;
  PrintRow('=', 100);
  std::cout << "First matrix\n";
  first_matrix.Print();
  PrintRow('=', 100);
  std::cout << "Second matrix\n";
  second_matrix.Print();
  PrintRow('=', 100);
}

void View::PrintResult(const Matrix& matrix, Time start, Time finish) {
  matrix.Print();
  std::cout << "Time execution = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(finish -
                                                                     start)
                   .count()
            << " milliseconds\n";
  PrintRow('*', 100);
}

int View::CheckCorrectNumberInput(const std::string& message) const {
  std::cout << message;
  int input{};
  std::cin >> input;
  if (std::cin.fail() || input < 1) {
    std::cin.clear();
    std::cin.ignore();
    throw std::invalid_argument("Incorrect input data");
  }
  return input;
}

double View::MatrixElementInput() {
  double input{};
  std::cin >> input;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore();
    throw std::invalid_argument("Incorrect input data");
  }
  return input;
}

void View::FillMatrix() {
  while (true) {
    PrintRow('*', 100);
    std::cout << "Select matrix fill method: \n";
    PrintRow('_', 100);
    std::cout << "1) Fill matrix from console\n";
    std::cout << "2) Random fill matrix\n";
    PrintRow('_', 100);
    int method_choise{0};
    method_choise = CheckCorrectNumberInput("");
    if (method_choise == 1) {
      InputFromConsole();
      break;
    }
    if (method_choise == 2) {
      FillRandom();
      break;
    }
    std::cout << "\nSelected method should be 1 or 2. Try again!\n\n";
  }
}

void View::InputFromConsole() {
  int row1 = CheckCorrectNumberInput(
      "Input the number of rows of the first matrix : ");
  int col1 = CheckCorrectNumberInput(
      "Input the number of columns of the first matrix : ");
  std::cout << "Input first matrix elements\n";
  Matrix a(row1, col1);
  for (int i = 0; i < row1; ++i) {
    for (int j = 0; j < col1; ++j) {
      a(i, j) = MatrixElementInput();
    }
  }

  int row2 = CheckCorrectNumberInput(
      "Input the number of rows of the second matrix : ");
  int col2 = CheckCorrectNumberInput(
      "Input the number of columns of the second matrix : ");
  std::cout << "Input second matrix elements\n";
  Matrix b(row2, col2);
  for (int i = 0; i < row2; ++i) {
    for (int j = 0; j < col2; ++j) {
      b(i, j) = MatrixElementInput();
    }
  }
  controller_ = new Controller(a, b);
}

void View::FillRandom() {
  int row1 = CheckCorrectNumberInput(
      "Input the number of rows of the first matrix : ");
  int col1 = CheckCorrectNumberInput(
      "Input the number of columns of the first matrix : ");
  Matrix a(row1, col1);
  a.RandomMatrix();

  int row2 = CheckCorrectNumberInput(
      "Input the number of rows of the second matrix : ");
  int col2 = CheckCorrectNumberInput(
      "Input the number of columns of the second matrix : ");
  Matrix b(row2, col2);
  b.RandomMatrix();

  controller_ = new Controller(a, b);
}

void View::PrintMulMatrix(const std::string& message, int iter,
                          std::function<Matrix()> operation) {
  std::cout << std::endl << message << std::endl;
  Matrix result;
  const auto start{std::chrono::system_clock::now()};
  for (int i = 0; i < iter; ++i) {
    result = operation();
  }
  const auto finish{std::chrono::system_clock::now()};
  PrintResult(result, start, finish);
}

void View::PrintMulMatrixParallel(const std::string& message, int iter,
                                  std::function<Matrix(size_t)> operation) {
  std::cout << std::endl << message << std::endl;
  std::cout << "Available threads: " << std::thread::hardware_concurrency()
            << std::endl;
  std::cout << "\nInput threads count: ";
  int threads = CheckCorrectNumberInput("");
  Matrix result;

  const auto start{std::chrono::system_clock::now()};
  for (int i = 0; i < iter; ++i) {
    result = operation(threads);
  }
  const auto finish{std::chrono::system_clock::now()};
  PrintResult(result, start, finish);
}

void View::PrintRow(char a, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    std::cout << a;
  }
  std::cout << std::endl;
}

/*std::vector<size_t> View::IterForThreads(size_t iter, size_t threads) {
        std::vector<size_t> result(threads);
        size_t remains = iter % threads;
        for (size_t i = 0; i < threads; ++i) {
                result[i] = iter / threads;
                if (remains) {
                        result[i] += 1;
                        --remains;
                }
        }
        return result;
}*/
}  // namespace s21
