#pragma once

#include "BinarySearchTreeNode.hpp"

template <typename Node>
class BinarySearchTree {
    private:
        using valueType = typename Node::valueType;
        void deleteSubTree(Node *node);

    protected:
        template <std::input_iterator Iter, typename Inserter> requires std::same_as<std::iter_value_t<Iter>, valueType>
        void insertRange(Iter begin, Iter end, Inserter inserter);
        
    public:
        Node *root;

        BinarySearchTree() : root(nullptr) {}
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, valueType>
        BinarySearchTree(Iter begin, Iter end);
        ~BinarySearchTree();

        virtual void insert(valueType &value, Node *node = nullptr);
        virtual void remove(valueType &value, Node *node = nullptr);

        valueType& minimum(Node *node = nullptr);
        valueType& maximum(Node *node = nullptr);
};

#include "BinarySearchTree.tpp"