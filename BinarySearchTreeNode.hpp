#pragma once

template <typename T>
class BinarySearchTreeNode {
    template <typename Node>
    friend class BinarySearchTree;

    private:
        using valueType = T;

    public:
        T value;
        BinarySearchTreeNode *left;
        BinarySearchTreeNode *right;

        BinarySearchTreeNode(T& val) : value(val), left(nullptr), right(nullptr) {}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTreeNode<T> &node) {
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

    os << ")";
    return os;
}
