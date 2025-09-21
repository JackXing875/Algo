#include <iostream>
#include <cstdint>

uint32_t rol(uint32_t x, unsigned n) {
    return (x << n) | (x >> (32 - n));
}

uint32_t ror(uint32_t x, unsigned n) {
    return (x >> n) | (x << (32 - n));
}

int main() {
    uint32_t x = 0xB6; // 1011 0110
    std::cout << rol(x, 2) << std::endl; // 循环左移
    std::cout << ror(x, 2) << std::endl; // 循环右移
    return 0;
}
