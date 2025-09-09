#include "../BinarySearchTree.hpp"
#include "RedBlackTreeNode.hpp"

template <typename T>
class RedBlackTree : public BinarySearchTree<RedBlackTreeNode<T>> {
    private:
        using Node = RedBlackTreeNode<T>;

        void fixInsert(Node *node);
        void fixRemove(Node *node);

    public:
        using BinarySearchTree<RedBlackTreeNode<T>>::BinarySearchTree;
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
        RedBlackTree(Iter begin, Iter end);
        
        void insert(const T &value, Node *node = nullptr) override;
        void remove(const T &value, Node *node = nullptr) override;
};

#include "RedBlackTree.tpp"