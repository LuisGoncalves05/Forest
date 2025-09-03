#pragma once

#include "BinarySearchTreeNode.hpp"

template <typename T>
class AvlTreeNode: public BinarySearchTreeNodeBase<T, AvlTreeNode<T>> {
    public:
        int height;

        AvlTreeNode(const T& val, AvlTreeNode<T> *parent = nullptr) : BinarySearchTreeNodeBase<T, AvlTreeNode<T>>(val, parent), height(1) {}

        const int getBalance() {
            const int hl = this->left ? this->left->height : 0;
            const int hr = this->right ? this->right->height : 0;
            return hl - hr;
        }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const AvlTreeNode<T> &node) {
    return os << "Height: " << node.height << ", " << static_cast<const BinarySearchTreeNodeBase<T, AvlTreeNode<T>>&>(node);
}