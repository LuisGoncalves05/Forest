#include <iostream>
#include <vector>
#include "trees.hpp"

int main() {
    std::vector<int> v({1, 2, 3, 4, 5, 6, 7});
    auto a = AVL<int>(v.begin(), v.end());
    std::cout << a << std::endl << "\n" << a.find(1) << a.find(0) << std::endl;
    return 0;
}