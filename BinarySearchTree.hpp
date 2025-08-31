#pragma once

#include "BinarySearchTreeNode.hpp"

template <typename Node>
class BinarySearchTree {
    private:
        using valueType = typename Node::valueType;

    public:
        Node *root;

        BinarySearchTree() : root(nullptr) {}
        template <typename Iter>
        BinarySearchTree(Iter begin, Iter end);

        void insert(valueType &value);
        void insert(Node *node);
        void remove(valueType &value);
        void remove(Node *node);
};

#include "BinarySearchTree.tpp"