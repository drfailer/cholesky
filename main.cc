#include "cholesky.h"
#include "matrix.h"
#include "utils.h"
#include <cstring>
#include <iostream>

using MatrixType = double;

int main(int, char **) {
    constexpr size_t size = 3;
    MatrixType memA[size * size] = {
        4, 12, -16,
        12, 37, -43,
        -16, -43, 98
    };
    MatrixType memL[size * size];
    Matrix<MatrixType> A(size, size, memA);
    Matrix<MatrixType> L(size, size, memL);

    generateRandomMatrix(size, memA, memL);

    std::cout << "A:" << std::endl;
    std::cout << A << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "expected L:" << std::endl;
    std::cout << L << std::endl;

    memset(memL, 0, sizeof(MatrixType) * size * size);
    choleskyBanachiewicz(A, L);
    std::cout << "-----------------" << std::endl;
    std::cout << "found L:" << std::endl;
    std::cout << L << std::endl;
    return 0;
}
