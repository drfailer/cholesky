#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP
#include "matrix.h"
#include <cmath>
#include <stdexcept>
#include <lapack.h>

template <typename T>
void choleskyBanachiewicz(Matrix<T> &matrix) {
  for (size_t i = 0; i < matrix.height(); i++) {
    for (size_t j = 0; j <= i; j++) {
      T sum = 0;
      for (size_t k = 0; k < j; k++) {
        sum += (matrix.at(i, k) * matrix.at(j, k));
      }

      if (j == i) {
        matrix.at(j, j) = sqrt(matrix.at(j, j) - sum);
      } else {
        matrix.at(i, j) = (matrix.at(i, j) - sum) / matrix.at(j, j);
      }
    }
  }
}

template <typename T>
void choleskyLapack(Matrix<T> &matrix) {
  int32_t n = matrix.height();
  int32_t lda = matrix.width();
  int32_t info = 0;
  LAPACK_dpotrf((char*) "U", &n, matrix.get(), &lda, &info);
}

template <typename T>
void choleskySolverLapack(Matrix<T> &matrix, Matrix<T> &result) {
  int32_t n = matrix.height();
  int32_t nrhs = 1;
  int32_t lda = matrix.width();
  int32_t ldb = result.height();
  int32_t info = 0;
  LAPACK_dposv((char*) "U", &n, &nrhs, matrix.get(), &lda, result.get(), &ldb, &info);
}

#endif
