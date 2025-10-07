#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

namespace linalg {

// ---------------------------
//  向量运算
// ---------------------------
template <typename T>
std::vector<T> add(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vector size mismatch");
    std::vector<T> res(a.size());
    for (size_t i = 0; i < a.size(); ++i) res[i] = a[i] + b[i];
    return res;
}

template <typename T>
std::vector<T> subtract(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vector size mismatch");
    std::vector<T> res(a.size());
    for (size_t i = 0; i < a.size(); ++i) res[i] = a[i] - b[i];
    return res;
}

template <typename T>
T dot(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vector size mismatch");
    T sum = 0;
    for (size_t i = 0; i < a.size(); ++i) sum += a[i] * b[i];
    return sum;
}

template <typename T>
std::vector<T> scalar_mul(const std::vector<T>& v, T k) {
    std::vector<T> res(v.size());
    for (size_t i = 0; i < v.size(); ++i) res[i] = v[i] * k;
    return res;
}

// ---------------------------
//  矩阵运算
// ---------------------------
template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
Matrix<T> transpose(const Matrix<T>& A) {
    size_t rows = A.size(), cols = A[0].size();
    Matrix<T> B(cols, std::vector<T>(rows));
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            B[j][i] = A[i][j];
    return B;
}

template <typename T>
Matrix<T> multiply(const Matrix<T>& A, const Matrix<T>& B) {
    if (A[0].size() != B.size()) throw std::invalid_argument("Matrix dimension mismatch");
    size_t m = A.size(), n = B[0].size(), p = A[0].size();
    Matrix<T> C(m, std::vector<T>(n, 0));
    for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < n; ++j)
            for (size_t k = 0; k < p; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// ---------------------------
//  输出打印工具
// ---------------------------
template <typename T>
void print_vector(const std::vector<T>& v) {
    std::cout << "[ ";
    for (auto& x : v) std::cout << std::setw(6) << x << " ";
    std::cout << "]\n";
}

template <typename T>
void print_matrix(const Matrix<T>& M) {
    for (auto& row : M) {
        for (auto& x : row)
            std::cout << std::setw(8) << x << " ";
        std::cout << "\n";
    }
    std::cout << std::endl;
}

} // namespace linalg
