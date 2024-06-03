#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP
#include "matrix.h"
#include <cmath>
#include <stdexcept>
#include <lapack.h>

template <typename Type>
void choleskyBanachiewicz(Matrix<Type> &matrix) {
  for (size_t i = 0; i < matrix.height(); i++) {
    for (size_t j = 0; j <= i; j++) {
      Type sum = 0;
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

template <typename Type>
void choleskyLapack(Matrix<Type> &A) {
  int32_t n = A.height();
  int32_t lda = A.width();
  int32_t info = 0;
  /* LAPACK_dpotf2((char*) "U", &n, A.get(), &lda, &info); */
  LAPACK_dpotrf2((char*) "U", &n, A.get(), &lda, &info);
}

#endif
