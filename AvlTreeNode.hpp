#pragma once

template <typename T>
class AvlTreeNode: public BinarySearchTreeNode<T> {
    public:
        int balanceFactor;
        AvlTreeNode(T& val) : BinarySearchTreeNode(val), balanceFactor(0) {}
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const AvlTreeNode<T> &node) {
    os << "Node(value: " << node.value;

    os << ", left: ";
    if (node.left) {
        os << *node.left;
    } else {
        os << "nullptr";
    }

    os << ", right: ";
    if (node.right) {
        os << *node.right;
    } else {
        os << "nullptr";
    }

    os << ", balance factor: " << node.balanceFactor;

    os << ")";
    return os;
}