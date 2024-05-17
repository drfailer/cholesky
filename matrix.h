#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
#include <ostream>

template <typename T>
class Matrix {
  public:
    Matrix(size_t width, size_t height, T *ptr):
        width_(width), height_(height), ptr_(ptr) {}

    size_t width() const { return width_; }
    size_t height() const { return height_; }

    T at(size_t row, size_t col) const { return ptr_[row * width_ + col]; }
    T &at(size_t row, size_t col) { return ptr_[row * width_ + col]; }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for (size_t row = 0; row < matrix.height(); ++row) {
            for (size_t col = 0; col < matrix.width(); ++col) {
                os << matrix.at(col, row) << " ";
            }
            os << std::endl;
        }
        return os;
    }

  private:
    size_t width_ = 0;
    size_t height_ = 0;
    T *ptr_ = nullptr;
};

#endif
