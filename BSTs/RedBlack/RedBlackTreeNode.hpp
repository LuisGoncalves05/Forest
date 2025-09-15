#pragma once

#include "../BinarySearchTreeNode.hpp"

template <typename T>
class RedBlackTreeNode: public BinarySearchTreeNodeBase<T, RedBlackTreeNode<T>> {
    private:
        using Node = RedBlackTreeNode<T>;

    public:
        enum class Color {
            RED, BLACK
        };

        Color color;

        RedBlackTreeNode(const T& val, 
            Node *parent = nullptr, 
            Node *left = nullptr, 
            Node *right = nullptr, 
            Color color = Color::RED)
        : BinarySearchTreeNodeBase<T, Node>(
            val, 
            parent, 
            left,
            right
        ), color(color) {}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const RedBlackTreeNode<T> &node) {
    os << "RBNode(color: " 
       << (node.color == RedBlackTreeNode<T>::Color::RED ? "red" : "black")
       << ", parent: ";
    if (node.parent == nullptr) {
        os << "nil";
    } else {
        os << node.parent->value;
    }
    os << ", value: " << node.value << ", left: ";
    if (node.left == nullptr) {
        os << "nil";
    } else {
        os << *node.left;
    }
    os << ", right: ";
    if (node.right == nullptr) {
        os << "nil";
    } else {
        os << *node.right;
    }
    return os << ")";
}