#include "cholesky.h"
#include "matrix.h"
#include "utils.h"
#include <cassert>
#include <chrono>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cblas.h>

using MatrixType = double;

template <typename T>
std::pair<Matrix<T>, Matrix<T>>
initMatrix(std::string const &filename) {
  std::ifstream fs(filename);
  size_t width, height;

  // make openblas using only one thread
  /* openblas_set_num_threads(0); */
  /* openblas_set_num_threads(1); */
  /* openblas_set_num_threads(20); */
  openblas_set_num_threads(40);
  std::cout << "parallel? : " << openblas_get_parallel() << std::endl;
  std::cout << "num threads: " << openblas_get_num_threads() << std::endl;;

  fs >> width >> height;
  Matrix<T> matrix(width, height, new T[width * height]());
  Matrix<T> expected(width, height, new T[width * height]());

  for (size_t i = 0; i < width * height; ++i) {
    fs >> matrix.get()[i];
  }

  fs >> width >> height;
  for (size_t i = 0; i < width * height; ++i) {
    fs >> expected.get()[i];
  }

  return std::make_pair(matrix, expected);
}


int main(int argc, char **argv) {
  if (argc < 2) {
    throw std::invalid_argument("error: input file name must be provided");
  }
  auto result = initMatrix<MatrixType>(argv[1]);
  auto matrix = result.first;
  auto expected = result.second;


  if (argc > 2) {
    /* std::cout << "using lapack function:" << std::endl; */
    auto begin = std::chrono::system_clock::now();
    choleskyLapack(matrix);
    auto end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
  } else {
    /* std::cout << "using normal function:" << std::endl; */
    auto begin = std::chrono::system_clock::now();
    choleskyBanachiewicz(matrix);
    auto end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
  }

  if (!verifySoluton(matrix, expected)) {
    std::cout << "ERROR" << std::endl;
  }
  delete[] matrix.get();
  delete[] expected.get();
  return 0;
}
