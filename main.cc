#include "cholesky.h"
#include "matrix.h"
#include "utils.h"
#include <cblas.h>
#include <chrono>
#include <iostream>
#include <stdexcept>

using MatrixType = double;


int main(int argc, char **argv) {
  if (argc < 2) {
    throw std::invalid_argument("error: input file name must be provided");
  }
  auto input = initMatrix<MatrixType>(argv[1]);
  auto matrix = input.matrix;
  auto result = input.result;
  auto expected = input.expected;
  auto solution = input.solution;

  if (argc > 2) {
    openblas_set_num_threads(std::stoi(argv[2]));
    auto begin = std::chrono::system_clock::now();
//    choleskyLapack(matrix);
    choleskySolverLapack(matrix, result);
    auto end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms"
              << std::endl;
  } else {
    auto begin = std::chrono::system_clock::now();
    choleskyBanachiewicz(matrix);
    auto end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << "ms" << std::endl;
  }

  if (!verifyMatrix(matrix, expected, 10e-3)) {
    std::cout << "ERROR: wrong matrix" << std::endl;
  }
  if (argc > 2 && !verifySolution(result, solution, 10e-3)) {
    std::cout << "ERROR: wrong vector" << std::endl;
  }
  delete[] matrix.get();
  delete[] result.get();
  delete[] expected.get();
  delete[] solution.get();
  return 0;
}
