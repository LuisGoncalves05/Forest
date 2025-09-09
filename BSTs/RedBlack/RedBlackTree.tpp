#pragma once

#include <iostream>

template <typename T>
void RedBlackTree<T>::fixInsert(Node *node) {
    if (node == nullptr) return;

    while (node != this->root && node->parent->color == RedBlackTreeNode<T>::Color::RED) {
        Node *parent = node->parent;
        Node *grandparent = parent->parent;
        if (grandparent == nullptr) break; // Possible case 0: parent is root, handled outside loop
        Node *uncle = grandparent->left == parent ? grandparent->right : grandparent->left;
        typename RedBlackTreeNode<T>::Color uncleColor = RedBlackTreeNode<T>::getColor(uncle);

        if (uncleColor == RedBlackTreeNode<T>::Color::RED) { // Case 1: Red Uncle
            parent->color = RedBlackTreeNode<T>::Color::BLACK;
            if (uncle) uncle->color = RedBlackTreeNode<T>::Color::BLACK;
            grandparent->color = RedBlackTreeNode<T>::Color::RED;
            node = grandparent; // Check up if needed
        } else if (uncleColor == RedBlackTreeNode<T>::Color::BLACK) {
            if ((node == parent->left && parent == grandparent->right)) { // Case 2: Black Uncle Triangle Right Left
                this->rightRotate(parent);
                node = parent;
                parent = node->parent;
            } else if (node == parent->right && parent == grandparent->left) { // Case 2: Black Uncle Triangle Left Right
                this->leftRotate(parent);
                node = parent;
                parent = node->parent;
            }
            parent->color = RedBlackTreeNode<T>::Color::BLACK;
            grandparent = parent->parent;
            grandparent->color = RedBlackTreeNode<T>::Color::RED;
            // Case 3: Black Uncle Line
            if (parent == grandparent->right) {
                this->leftRotate(grandparent);
            } else { // parent == grandparent->left
                this->rightRotate(grandparent);
            }
            break;
        }
    }
    this->root->color = RedBlackTreeNode<T>::Color::BLACK; // Case 0: Red Root
}

template <typename T>
void RedBlackTree<T>::fixRemove(Node *node) {
    if (node == nullptr) return;

    return;
}

template <typename T> template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
RedBlackTree<T>::RedBlackTree(Iter begin, Iter end) {
    this->insertRange(begin, end, [&](T &value) {this->insert(value);});
}

template <typename T> 
void RedBlackTree<T>::insert(const T &value, Node *node) {
    if (this->root == nullptr) {
        this->root = new Node(value);
        fixInsert(this->root);
        return;
    }

    Node *current = node == nullptr ? this->root : node;
    while (true) {
        if (value < current->value) {
            if (current->left) {
                current = current->left;
            } else {
                current->left = new Node(value, current);
                fixInsert(current->left);
                return;
            }
        } else if (value > current->value) {
            if (current->right) {
                current = current->right;
            } else {
                current->right = new Node(value, current);
                fixInsert(current->right);
                return;
            }
        } else {
            std::cout << "Already have an equal node: " << value << "\n";
            return;
        }
    }
}

template <typename T> 
void RedBlackTree<T>::remove(const T &value, Node *node) {
    Node *previous = nullptr;
    Node *current = node == nullptr ? this->root : node;
    while (true) {
        if (value < current->value) {
            if (current->left) {
                previous = current;
                current = current->left;
            } else {
                std::cout << "Node not found: " << node->value << "\n";
                return;
            }
        } else if (value > current->value) {
            if (current->right) {
                previous = current;
                current = current->right;
            } else {
                std::cout << "Node not found: " << node->value << "\n";
                return;
            }
        } else {
            if (!current->left && !current->right) { // No children
                if (current == this->root) {
                    this->root = nullptr;
                } else if (current == previous->left) {
                    previous->left = nullptr;
                } else if (current == previous->right) {
                    previous->right = nullptr;
                }
            } else if ((!current->left && current->right) || (current->left && !current->right)) { // 1 child
                Node *child = current->left ? current->left : current->right;
                if (current == this->root) {
                    this->root = child;
                    this->root->parent = nullptr;
                } else {
                    if (current == previous->left) {
                        previous->left = child;
                    } else if (current == previous->right) {
                        previous->right = child;
                    }
                    child->parent = previous;
                }
            } else { // 2 children
                const T &m = this->minimum(current->right);
                remove(m, current);

                Node *min = new Node(m, previous);
                min->left = current->left;
                min->right = current->right;
                current->left->parent = min;
                current->right->parent = min;

                if (current == this->root) {
                    this->root = min;
                } else if (current == previous->left) {
                    previous->left = min;
                } else if (current == previous->right) {
                    previous->right = min;
                }
            }
            delete current;
            return;
        }
    }

    fixRemove(previous);
}