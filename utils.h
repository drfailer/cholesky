#ifndef UTILS_HPP
#define UTILS_HPP
#include "matrix.h"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <fstream>

/******************************************************************************/
/* test functions                                                             */
/******************************************************************************/

template<typename Type>
bool verifyMatrix(Matrix<Type> founded, Matrix<Type> expected, Type precision) {
  bool result = true;

  for (size_t i = 0; i < expected.height(); ++i) {
    for (size_t j = 0; j <= i; ++j) {
      if (!((founded.at(i, j) - precision) <= expected.at(i, j) &&
            expected.at(i, j) <= (founded.at(i, j) + precision))) {
        result = false;
      }
    }
  }
  return result;
}

template<typename Type>
bool verifySolution(Matrix<Type> founded, Matrix<Type> expected, Type precision) {
  bool result = true;
  size_t size = expected.height() * expected.width();

  for (size_t i = 0; i < size; ++i) {
    if (!((founded.get()[i] - precision) <= expected.get()[i] &&
          expected.get()[i] <= (founded.get()[i] + precision))) {
      result = false;
    }
  }
  return result;
}

/******************************************************************************/
/* init                                                                       */
/******************************************************************************/

template <typename T>
struct InitType {
  InitType(Matrix<T> &matrix, Matrix<T> &result, Matrix<T> &expected, Matrix<T> &solution):
    matrix(matrix), result(result), expected(expected), solution(solution) {}

  Matrix<T> matrix;
  Matrix<T> result;
  Matrix<T> expected;
  Matrix<T> solution;
};

template <typename T>
InitType<T> initMatrix(std::string const &filename) {
  std::ifstream fs(filename, std::ios::binary);
  size_t width, height;

  // parse the size
  fs.read(reinterpret_cast<char *>(&width), sizeof(width));
  fs.read(reinterpret_cast<char *>(&height), sizeof(height));

  Matrix<T> matrix(width, height, new T[width * height]());
  Matrix<T> result(1, height, new T[height]());
  Matrix<T> expected(width, height, new T[width * height]());
  Matrix<T> solution(1, height, new T[height]());

  // parse the symmetric matrix
  for (size_t i = 0; i < width * height; ++i) {
    fs.read(reinterpret_cast<char *>(matrix.get() + i), sizeof(matrix.get()[i]));
  }

  // parse the result vector
  for (size_t i = 0; i < height; ++i) {
    fs.read(reinterpret_cast<char *>(result.get() + i), sizeof(result.get()[i]));
  }

  // parse the expected matrix
  for (size_t i = 0; i < width * height; ++i) {
    fs.read(reinterpret_cast<char *>(expected.get() + i), sizeof(expected.get()[i]));
  }

  // parse the solution matrix
  for (size_t i = 0; i < height; ++i) {
    fs.read(reinterpret_cast<char *>(solution.get() + i), sizeof(solution.get()[i]));
  }
  return InitType(matrix, result, expected, solution);
}

#endif
