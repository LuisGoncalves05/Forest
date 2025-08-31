#pragma once

#include <iostream>

template <typename Node> template <typename Iter>
BinarySearchTree<Node>::BinarySearchTree(Iter begin, Iter end) {
    for (Node *element = begin; element != end; element++) {
        insert(element);
    }
}

template <typename Node>
void BinarySearchTree<Node>::insert(valueType &value) {
    Node *node = new Node(value);
    insert(node);
}

template <typename Node>
void BinarySearchTree<Node>::insert(Node *node) {
    if (root == nullptr) {
        root = node;
        return;
    }

    Node *current = root;
    while (true) {
        if (node->value < current->value) {
            if (current->left) {
                current = current->left;
            } else {
                current->left = node;
                return;
            }
        } else if (node->value > current->value) {
            if (current->right) {
                current = current->right;
            } else {
                current->right = node;
                return;
            }
        } else {
            std::cout << "Already have an equal node: " << node->value << "\n";
            return;
        }
    }
}

template <typename Node>
void BinarySearchTree<Node>::remove(valueType &value) {
    Node *node = new Node(value);
    remove(node);
}

template <typename Node>
void BinarySearchTree<Node>::remove(Node *node) {
    Node *previous = nullptr;
    Node *current = root;
    while (true) {
        if (node->value < current->value) {
            if (current->left) {
                previous = current;
                current = current->left;
            } else {
                std::cout << "Node not found: " << node->value << "\n";
                return;
            }
        } else if (node->value > current->value) {
            if (current->right) {
                previous = current;
                current = current->right;
            } else {
                std::cout << "Node not found: " << node->value << "\n";
                return;
            }
        } else {
            if (current == root) {
                delete root;
                root = nullptr;
            } else if (previous->left && current->value == previous->left->value) {
                Node *l = previous->left;
                previous->left = l->right;
                delete l;
            } else {
                Node *r = previous->right;
                previous->right = r->right;
                delete r;
            }
            return;
        }
    }
}

template <typename Node>
std::ostream &operator<<(std::ostream &os, const BinarySearchTree<Node> &tree) {
    os << "Tree(root: ";
    if (tree.root) {
        os << *tree.root;
    } else {
        os << "nullptr";
    }

    os << ")";
    return os;
}