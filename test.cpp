#include <iostream>
#include <vector>
#include "trees.hpp"

int main() {
    std::vector<int> v({1, 5, 10, 6, 2, 3, 12, 11});
    auto a = RBT<int>(v.begin(), v.end());
    std::cout << a << std::endl << a.find(1) << a.find(0) << std::endl;
    return 0;
}