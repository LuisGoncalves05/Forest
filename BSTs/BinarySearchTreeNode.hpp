#pragma once

template <typename T, typename NodeType>
class BinarySearchTreeNodeBase {
    template <typename Node>
    friend class BinarySearchTree;

    private:
        using valueType = T;

    public:
        const T value;
        NodeType* parent;
        NodeType* left;
        NodeType* right;

        BinarySearchTreeNodeBase(const T& val, NodeType *parent = nullptr, NodeType *left = nullptr, NodeType *right = nullptr) : value(val), parent(parent), left(left), right(right) {}
};

template <typename T>
class BinarySearchTreeNode : public BinarySearchTreeNodeBase<T, BinarySearchTreeNode<T>> {
    using BinarySearchTreeNodeBase<T, BinarySearchTreeNode<T>>::BinarySearchTreeNodeBase;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const BinarySearchTreeNode<T> &node) {
    os << "BSTNode(value: " << node.value;

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

    return os << ")";
}