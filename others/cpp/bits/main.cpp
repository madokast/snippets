#include <iostream>

int main() {
    int a = 0;
    std::cout << a << std::endl;
    std::cout << (a>>1) << std::endl;
    std::cout << (a & (a>>1)) << std::endl;
}