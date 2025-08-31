#include <iostream>
#include "BinarySearchTree.hpp"

int main() {
    auto a = BinarySearchTree<BinarySearchTreeNode<int>>();
    int s = 2, m = 1, n = 3, o = 5;
    a.insert(s);
    a.insert(m);
    a.insert(n);
    a.insert(o);
    std::cout << a << std::endl;
    a.remove(o);
    std::cout << a << std::endl;
    a.remove(n);
    std::cout << a << std::endl;
    a.remove(m);
    std::cout << a << std::endl;
    a.remove(s);
    std::cout << a << std::endl;
}