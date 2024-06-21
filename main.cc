#include "cholesky.h"
#include "matrix.h"
#include "utils.h"
#include <cblas.h>
#include <chrono>
#include <iostream>
#include <stdexcept>
#define NB_MEASURES 2

using MatrixType = double;

template <typename T>
void testLapack(Matrix<T> &matrix, Matrix<T> &result, size_t nbThreads) {
  auto begin = std::chrono::system_clock::now();
  choleskySolverLapack(matrix, result);
  auto end = std::chrono::system_clock::now();
  std::cout << matrix.width() << " " << nbThreads << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms"
    << std::endl;
}

template <typename T>
void verifySolution(Problem<T> problem) {
  if (!verifyMatrix(problem.matrix, problem.expectedMatrix, 10e-3)) {
    std::cout << "ERROR: wrong matrix" << std::endl;
  }
  if (!verifySolution(problem.result, problem.expectedSolution, 10e-3)) {
    std::cout << "ERROR: wrong vector" << std::endl;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    throw std::invalid_argument("error: input file name must be provided");
  }
  auto problem = initMatrix<MatrixType>(argv[1]);

  if (argc > 2) {
    size_t nbThreads = std::atol(argv[2]);
    openblas_set_num_threads(nbThreads);
    testLapack(problem.matrix, problem.result, nbThreads);
    verifySolution(problem);
  } else {
    for (size_t nbThreads = 5; nbThreads <= 40; nbThreads += 5) {
      openblas_set_num_threads(nbThreads);
      for (size_t nbMeasures = 0; nbMeasures < NB_MEASURES; ++nbMeasures) {
        testLapack(problem.matrix, problem.result, nbThreads);
        verifySolution(problem);
        problem.matrix.reset(problem.baseMatrix);
        problem.result.reset(problem.baseResult);
      }
    }
  }

  return 0;
}
