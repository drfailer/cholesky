#include "cholesky.h"
#include "matrix.h"
#include "utils.h"
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cblas.h>

using MatrixType = double;

template <typename T>
std::pair<Matrix<T>, Matrix<T>>
initMatrix(std::string const &filename) {
  std::ifstream fs(filename, std::ios::binary);
  size_t width, height;

  fs.read(reinterpret_cast<char*>(&width), sizeof(width));
  fs.read(reinterpret_cast<char*>(&height), sizeof(height));
  Matrix<T> matrix(width, height, new T[width * height]());
  Matrix<T> expected(width, height, new T[width * height]());

  for (size_t i = 0; i < width * height; ++i) {
    fs.read(reinterpret_cast<char*>(matrix.get() + i), sizeof(matrix.get()[i]));
  }

  fs.read(reinterpret_cast<char*>(&width), sizeof(width));
  fs.read(reinterpret_cast<char*>(&height), sizeof(height));

  for (size_t i = 0; i < width * height; ++i) {
    fs.read(reinterpret_cast<char*>(expected.get() + i), sizeof(expected.get()[i]));
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
    openblas_set_num_threads(atoi(argv[2]));
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
