#include <iostream>
#include "trees.hpp"

int main() {
    auto a = AVL<int>();
    int s = 5, m = 4, n = 3, o = 2;
    a.insert(s);
    a.insert(m);
    a.insert(n);
    a.insert(o);
    std::cout << a << std::endl;
    a.remove(s);
    std::cout << a << std::endl;
    a.remove(m);
    std::cout << a << std::endl;
    a.remove(n);
    std::cout << a << std::endl;
    a.remove(o);
    std::cout << a << std::endl;
}