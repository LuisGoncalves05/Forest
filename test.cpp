#include <iostream>
#include <vector>
#include "trees.hpp"

int main() {
    std::vector<int> v({1, 5, 10, 6, 2, 3, 12, 11});
    auto a = RBT<int>(v.begin(), v.end());
    a.remove(5);
    std::cout << a << std::endl;
    
    a.remove(10);
    std::cout << a << std::endl;
    
    a.remove(2);
    std::cout << a << std::endl;
    
    a.remove(3);
    std::cout << a << std::endl;
    
    a.remove(11);
    std::cout << a << std::endl;
    
    a.remove(1);
    std::cout << a << std::endl;
    
    a.remove(12);
    std::cout << a << std::endl;
    
    a.remove(6);
    std::cout << a << std::endl;

    return 0;
}