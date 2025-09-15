#pragma once

#include "BinarySearchTreeNode.hpp"

template <typename Node>
class BinarySearchTree {
    private:
        using valueType = typename Node::valueType;
        template <typename N> friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree<N> &tree);

        virtual void deleteSubTree(Node *node);
    protected:
        Node *root;
        template <std::input_iterator Iter, typename Inserter> requires std::same_as<std::iter_value_t<Iter>, valueType>
        void insertRange(Iter begin, Iter end, Inserter inserter);

        void leftRotate(Node *node);
        void rightRotate(Node *node);

        Node *minimumNode(Node* node);
        Node *maximumNode(Node* node);

        const valueType &minimum(Node* node);
        const valueType &maximum(Node* node);
        
    public:
        BinarySearchTree() : root(nullptr) {}
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, valueType>
        BinarySearchTree(Iter begin, Iter end);
        virtual ~BinarySearchTree();

        virtual void insert(const valueType &value, Node *node = nullptr);
        virtual void remove(const valueType &value, Node *node = nullptr);
        virtual int maxHeight();
        virtual int maxHeight(Node *node);


        virtual const valueType &minimum();
        virtual const valueType &maximum();
        virtual bool find(const valueType &value);
};

#include "BinarySearchTree.tpp"