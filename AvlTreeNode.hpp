#pragma once

#include "BinarySearchTreeNode.hpp"

template <typename T>
class AvlTreeNode: public BinarySearchTreeNodeBase<T, AvlTreeNode<T>> {
    public:
        int height;

        AvlTreeNode(T& val, AvlTreeNode<T> *parent = nullptr) : BinarySearchTreeNodeBase<T, AvlTreeNode<T>>(val, parent), height(1) {}

        int getBalance() {
            int hl = this->left ? this->left->height : 0;
            int hr = this->right ? this->right->height : 0;
            return hl - hr;
        }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const AvlTreeNode<T> &node) {
    return os << "Height: " << node.height << ", " << static_cast<const BinarySearchTreeNodeBase<T, AvlTreeNode<T>>&>(node);
}