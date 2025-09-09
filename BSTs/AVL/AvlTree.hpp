#include "../BinarySearchTree.hpp"
#include "AvlTreeNode.hpp"

template <typename T>
class AvlTree : public BinarySearchTree<AvlTreeNode<T>> {
    private:
        using Node = AvlTreeNode<T>;

        void updateHeights(Node *node);
        void balance(Node *node);

        void leftRotate(Node *node);
        void rightRotate(Node *node);

        void leftLeft(Node *node);
        void leftRight(Node *node);
        void rightLeft(Node *node);
        void rightRight(Node *node);

    public:
        using BinarySearchTree<AvlTreeNode<T>>::BinarySearchTree;
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
        AvlTree(Iter begin, Iter end);
        
        void insert(const T &value, Node *node = nullptr) override;
        void remove(const T &value, Node *node = nullptr) override;
};

#include "AvlTree.tpp"