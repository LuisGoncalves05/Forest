#include "../BinarySearchTree.hpp"
#include "RedBlackTreeNode.hpp"

template <typename T>
class RedBlackTree : public BinarySearchTree<RedBlackTreeNode<T>> {
    private:
        using Node = RedBlackTreeNode<T>;
        template <typename U> friend std::ostream &operator<<(std::ostream &os, const RedBlackTree<U> &tree);

        void fixInsert(Node *node);
        void fixRemove(Node *node, Node *nodeParent);

        /* for handling nullptr */
        Node *getParent(Node *node);
        void setParent(Node *node, Node *parent);
        Node *getLeft(Node *node);
        void setLeft(Node *node, Node *left);
        Node *getRight(Node *node);
        void setRight(Node *node, Node *right);
        Node::Color getColor(Node *node);
        void setColor(Node *node, Node::Color color);
        const T getValue(Node *node);
        void setValue(Node *node, const T &value);

    public:
        using BinarySearchTree<RedBlackTreeNode<T>>::BinarySearchTree;
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
        RedBlackTree(Iter begin, Iter end);
        
        void insert(const T &value) override;
        void remove(const T &value, Node *node = nullptr) override;
};

#include "RedBlackTree.tpp"