#include <iostream>

template <typename T>
bool compare(T a, T b)
{
    return !(a ^ b);
}

int main(int argc, char *argv[])
{
    int a = 3, b = 5;
    int x = 1, y = 1;
    std::cout << compare(a, b) << std::endl;
    std::cout << compare(x, y) << std::endl;
    return 0;
}