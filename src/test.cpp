#include "LinAlg.hpp"
using namespace linalg;

int main() {
    std::vector<double> a = {1, 2, 3};
    std::vector<double> b = {4, 5, 6};

    auto c = add(a, b);
    print_vector(c);

    Matrix<double> A = {{1, 2}, {3, 4}};
    Matrix<double> B = {{2, 0}, {1, 2}};
    auto C = multiply(A, B);
    print_matrix(C);

    return 0;
}
