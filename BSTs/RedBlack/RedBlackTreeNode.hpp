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

        static Color getColor(Node *node) {
            return node ? node->color : Color::BLACK;
        }

        Color color;

        RedBlackTreeNode(const T& val, RedBlackTreeNode<T> *parent = nullptr) : BinarySearchTreeNodeBase<T, RedBlackTreeNode<T>>(val, parent), color(Color::RED) {}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const RedBlackTreeNode<T> &node) {
    return os << "Color: " << (node.color == RedBlackTreeNode<T>::Color::RED ? "Red" : "Black")  << ", " << static_cast<const BinarySearchTreeNodeBase<T, RedBlackTreeNode<T>>&>(node);
}
