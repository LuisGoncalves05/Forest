#include <gtest/gtest.h>
#include <cmath>
#include "../trees.hpp"


TEST(BSTRandomInsertTest, BasicAssertions) {
    srand(time(NULL));
    const int N = 1 << 21;

    std::vector<int> vec;
    std::set<int> stlSet;
    for (int i = 0; i < N; i++) {
        int el = rand() % (N << 3);
        auto [_, inserted] = stlSet.insert(el);
        if (inserted) vec.push_back(el);
    }

    auto mySet = BST<int>(vec.begin(), vec.end());

    for (size_t i = 0; i < stlSet.size(); i++) {
        int elements[2] = {*stlSet.begin(), *stlSet.rbegin()};
        int stlMin = elements[0];
        int stlMax = elements[1];
        EXPECT_EQ(stlMin, mySet.minimum());
        EXPECT_EQ(stlMax, mySet.maximum());
                
        EXPECT_EQ(mySet.find(stlMin), stlSet.count(stlMin));
        EXPECT_EQ(mySet.find(stlMin), true);
        EXPECT_EQ(mySet.find(stlMax), stlSet.count(stlMax));
        EXPECT_EQ(mySet.find(stlMax), true);

        int element = elements[i % 2];

        EXPECT_EQ(mySet.find(element), stlSet.count(element));
        EXPECT_EQ(mySet.find(element), true);

        mySet.remove(element);
        stlSet.erase(element);

        EXPECT_EQ(mySet.find(element), stlSet.count(element));
        EXPECT_EQ(mySet.find(element), false);
    }
}