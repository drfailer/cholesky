#ifndef UTILS_HPP
#define UTILS_HPP
#include "matrix.h"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <cstring>
#define timerStart() auto _start = std::chrono::system_clock::now();
#define timerEnd() auto _end = std::chrono::system_clock::now();
#define timerCount()                                                           \
    std::chrono::duration_cast<std::chrono::microseconds>(_end - _start)       \
            .count() /                                                         \
        1.0e6

/******************************************************************************/
/*                              generate problem                              */
/******************************************************************************/

template <typename Type>
void transpose(Type *matrix, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < i; ++j) {
            std::swap(matrix[i * size + j], matrix[j * size + i]);
        }
    }
}

template <typename Type>
void dot(Type *a, Type *c, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                c[i * size + j] += a[i * size + k] * a[j * size + k];
            }
        }
    }
}

template <typename Type>
void generateRandomMatrix(size_t size, Type *matrix, Type *result) {
    std::random_device dv;
    std::mt19937 gen(dv());
    /* std::uniform_real_distribution<> dis(-10, 10); */
    std::uniform_int_distribution<> dis(0, 10);

    memset(matrix, 0, sizeof(Type) * size * size);
    memset(result, 0, sizeof(Type) * size * size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            Type value = dis(gen);
            if (value == 0)
                value++; // make sure we don't have 0 on the diagonal
            result[i * size + j] = value;
        }
    }
    dot(result, matrix, size);
}

/******************************************************************************/
/*                               test functions                               */
/******************************************************************************/

template <typename Type>
bool isTriangular(Matrix<Type> const &matrix, Type precision) {
    for (size_t i = 0; i < matrix.height(); ++i) {
        for (size_t j = 0; j <= i; ++j) {
            bool isOne = (1 - precision) <= matrix.at(i, j) &&
                         matrix.at(i, j) <= (1 + precision);
            bool isZero =
                -precision <= matrix.at(i, j) && matrix.at(i, j) <= precision;
            if ((i == j && !isOne) || (i != j && !isZero)) {
                std::cout << i << ", " << j << ": " << matrix.at(i, j)
                          << std::endl;
                return false;
            }
        }
    }
    return true;
}

#endif
