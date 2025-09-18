#include <iostream>
#include <set>
#include <algorithm>
#include <cmath>
#include "trees.hpp"

int main() {/*
    const int N = 1 << 21;
    std::set<int> v;
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        int el = rand() % (N << 3);
        v.insert(el);
        //std::cout << el << ' ';
    }
    //std::cout << std::endl;

    auto a = RBT<int>(v.begin(), v.end());
    std::cout << a.maxHeight() << ' ' << std::floor(2*std::log2(v.size()+1)) << std::endl;

    auto b = AVL<int>(v.begin(), v.end());
    std::cout << b.maxHeight() << ' ' << std::floor(1.44*std::log2(v.size()+2)-0.328) << std::endl;

    for (size_t i = 0; i < v.size(); i++) {
        int el = *--v.end();
        a.remove(el);
        v.erase(el);
    }*/

    srand(0);
    const int N = 1 << 3;
    std::set<int> v;
    auto a = SPL<int>(v.begin(), v.end());
    for (int i = 0; i < N; i++) {
        int el = rand() % (N << 3);
        a.insert(el);
        v.insert(el);
        std::cout << el << std::endl;
        std::cout << a << std::endl;
    }

    std::cout << std::endl;

    while(v.size()) {
        int el = *--v.end();
        a.remove(el);
        v.erase(el);
        std::cout << el << std::endl;
        std::cout << a << std::endl;
    }

    return 0;
}