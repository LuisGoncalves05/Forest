#include <iostream>
#include <vector>
#include "trees.hpp"

int main() {
    auto v = std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8});
    auto a = AVL<int>(v.begin(), v.end());
    std::cout << a << std::endl;   
}