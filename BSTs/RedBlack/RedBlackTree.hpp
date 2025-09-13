#include "../BinarySearchTree.hpp"
#include "RedBlackTreeNode.hpp"

template <typename T>
class RedBlackTree : public BinarySearchTree<RedBlackTreeNode<T>> {
    private:
        using Node = RedBlackTreeNode<T>;
        template <typename U> friend std::ostream &operator<<(std::ostream &os, const RedBlackTree<U> &tree);

        void fixInsert(Node *node);
        void fixRemove(Node *node, Node *nodeParent);

        void transplant(Node *u, Node *v);

        void deleteSubTree(Node *node) override;

        void leftRotate(Node *node) override;
        void rightRotate(Node *node) override;

        Node *minimumNode(Node* node) override;
        Node *maximumNode(Node* node) override;

        const T &minimum(Node* node) override;
        const T &maximum(Node* node) override;
        
    public:
        RedBlackTree();
        template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
        RedBlackTree(Iter begin, Iter end);
        ~RedBlackTree();
        
        void insert(const T &value, Node *node = nullptr) override;
        void remove(const T &value, Node *node = nullptr) override;
        int maxHeight() override;
        int maxHeight(Node *node) override;

        const T &minimum() override;
        const T &maximum() override;

        bool find(const T &value) override;
};

#include "RedBlackTree.tpp"