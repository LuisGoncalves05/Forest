#pragma once

#include "BinarySearchTreeNode.hpp"

template <typename Node>
class BinarySearchTree {
    private:
        using valueType = typename Node::valueType;
        template <typename N>
        friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree<N> &tree);
        void deleteSubTree(Node *node);

    protected:
        Node *root;
        template <std::input_iterator Iter, typename Inserter> requires std::same_as<std::iter_value_t<Iter>, valueType>
        void insertRange(Iter begin, Iter end, Inserter inserter);
        
    public:

        BinarySearchTree() : root(nullptr) {}
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, valueType>
        BinarySearchTree(Iter begin, Iter end);
        virtual ~BinarySearchTree();

        virtual void insert(const valueType &value, Node *node = nullptr);
        virtual void remove(const valueType &value, Node *node = nullptr);

        const valueType &minimum(const Node *node = nullptr);
        const valueType &maximum(const Node *node = nullptr);
        bool find(const valueType &value);
};

#include "BinarySearchTree.tpp"