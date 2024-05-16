#ifndef UTILS_HPP
#define UTILS_HPP
#include <cstddef>
#include <random>
#include <iostream>
#include "matrix.h"
#include <chrono>
#define timerStart() auto _start = std::chrono::system_clock::now();
#define timerEnd() auto _end = std::chrono::system_clock::now();
#define timerCount()                                                           \
    std::chrono::duration_cast<std::chrono::microseconds>(_end - _start)       \
            .count() / 1.0e6

/******************************************************************************/
/*                              generate problem                              */
/******************************************************************************/

template <typename Type>
void generateRandomMatrix(size_t width, size_t height, Type *matrix) {
    std::random_device dv;
    std::mt19937 gen(dv());
    std::uniform_real_distribution<> dis(-10, 10);

    for (size_t i = 0; i < height; ++i) {
        Type sum = 0;
        for (size_t j = 0; j < width; ++j) {
            Type value = dis(gen);
            if (i == j && value == 0) value++; // make sure we don't have 0 on
                                               // the diagonal (normally, we should
                                               // exchange lines in this case
                                               // but it's not done yet in the
                                               // graph)
            matrix[i * width + j] = value;
        }
    }
}

/******************************************************************************/
/*                               test functions                               */
/******************************************************************************/

template <typename Type>
bool isTriangular(Matrix<Type> const& matrix, Type precision) {
    for (size_t i = 0; i < matrix.height(); ++i) {
        for (size_t j = 0; j <= i; ++j) {
            bool isOne = (1 - precision) <= matrix.at(i, j) && matrix.at(i, j) <= (1 + precision);
            bool isZero = -precision <= matrix.at(i, j) && matrix.at(i, j) <= precision;
            if ((i == j && !isOne) || (i != j && !isZero)) {
                    std::cout << i << ", " << j << ": " << matrix.at(i, j) << std::endl;
                    return false;
            }
        }
    }
    return true;
}

#endif
