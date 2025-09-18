#pragma once

#include "../BinarySearchTree.hpp"

template <typename T>
class SplayTree : public BinarySearchTree<BinarySearchTreeNode<T>> {
    private:
        using Node = BinarySearchTreeNode<T>;

        void zig(Node *node);
        void zag(Node *node);
        void zigZig(Node *node);
        void zigZag(Node *node);
        void zagZag(Node *node);
        void zagZig(Node *node);

        void splay(Node *node);
    
    public:
        using BinarySearchTree<BinarySearchTreeNode<T>>::BinarySearchTree;
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
        SplayTree(Iter begin, Iter end);

        void insert(const T &value) override;
        void remove(const T &value) override;

        bool find(const T &value) override;
};

#include "SplayTree.tpp"