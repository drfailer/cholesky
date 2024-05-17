#ifndef CHOLESKY_HPP
#define CHOLESKY_HPP
#include "matrix.h"
#include <cmath>
#include <stdexcept>

template <typename Type>
void choleskyBanachiewicz(Matrix<Type> const &A, Matrix<Type> &L) {
    for (size_t i = 0; i < A.height(); i++) {
        for (size_t j = 0; j <= i; j++) {
            Type sum = 0;
            for (size_t k = 0; k < j; k++) {
                sum += (L.at(i, k) * L.at(j, k));
            }

            if (j == i) {
                L.at(j, j) = sqrt(A.at(j, j) - sum);
            } else {
                L.at(i, j) = (A.at(i, j) - sum) / L.at(j, j);
            }
        }
    }
}

#endif
