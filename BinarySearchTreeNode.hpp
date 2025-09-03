#pragma once

template <typename T, typename NodeType>
class BinarySearchTreeNodeBase {
    template <typename Node>
    friend class BinarySearchTree;

    private:
        using valueType = T;

    public:
        const T value;
        NodeType* left;
        NodeType* right;
        NodeType* parent;

        BinarySearchTreeNodeBase(const T& val, NodeType *parent = nullptr) : value(val), left(nullptr), right(nullptr), parent(parent) {}
};

template <typename T, typename NodeType>
std::ostream &operator<<(std::ostream &os, const BinarySearchTreeNodeBase<T, NodeType> &node) {
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

template <typename T>
class BinarySearchTreeNode : public BinarySearchTreeNodeBase<T, BinarySearchTreeNode<T>> {
    public:
        BinarySearchTreeNode(const T& val, BinarySearchTreeNode<T>* parent = nullptr) : BinarySearchTreeNodeBase<T, BinarySearchTreeNode<T>>(val, parent) {}
};