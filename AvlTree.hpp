#include "BinarySearchTree.hpp"
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
        virtual void insert(T &value, Node *node = nullptr) override;
        virtual void remove(T &value, Node *node = nullptr) override;
};

#include "AvlTree.tpp"