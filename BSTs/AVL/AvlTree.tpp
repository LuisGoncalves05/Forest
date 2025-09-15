#pragma once

#include <iostream>

template <typename T>
void AvlTree<T>::updateHeights(Node *node) {
    if (node == nullptr) return;

    int hl = node->left ? node->left->height : 0;
    int hr = node->right ? node->right->height : 0;
    int newHeight = std::max(hl, hr) + 1;

    if (node->height != newHeight) {
        node->height = newHeight;
    }
    updateHeights(node->parent);
}

template <typename T>
void AvlTree<T>::balance(Node *node) {
    if (node == nullptr) return;

    int balance = node->getBalance();
    if (balance > 1) {
        if (node->left && node->left->getBalance() < 0) {
            leftRight(node);
        } else {
            leftLeft(node);
        }
    } else if (balance < -1) {
        if (node->right && node->right->getBalance() > 0) {
            rightLeft(node);
        } else { 
            rightRight(node);
        }
    }

    this->balance(node->parent);
}

template <typename T>
void AvlTree<T>::leftLeft(Node *node) {
    this->rightRotate(node);
    updateHeights(node);
}

template <typename T>
void AvlTree<T>::rightRight(Node *node) {
    this->leftRotate(node);
    updateHeights(node);
}

template <typename T>
void AvlTree<T>::leftRight(Node *node) {
    this->leftRotate(node->left);
    updateHeights(node->left);
    this->rightRotate(node);
    updateHeights(node);
}

template <typename T>
void AvlTree<T>::rightLeft(Node *node) {
    this->rightRotate(node->right);
    updateHeights(node->right);
    this->leftRotate(node);
    updateHeights(node);
}

template <typename T> template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
AvlTree<T>::AvlTree(Iter begin, Iter end) {
    this->insertRange(begin, end, [&](T value) {this->insert(value);});
}

template <typename T>
void AvlTree<T>::insert(const T &value) {
    if (this->root == nullptr) {
        this->root = new Node(value);
        return;
    }

    Node *current = this->root;
    while (true) {
        if (value < current->value) {
            if (current->left) {
                current = current->left;
            } else {
                current->left = new Node(value, current);
                break;
            }
        } else if (value > current->value) {
            if (current->right) {
                current = current->right;
            } else {
                current->right = new Node(value, current);
                break;
            }
        } else {
            std::cout << "Already have an equal node: " << value << "\n";
            return;
        }
    }

    updateHeights(current);
    balance(current);
}

template <typename T>
void AvlTree<T>::remove(const T &value) {
    Node *previous = nullptr;
    Node *current = this->root;
    while (true) {
        if (value < current->value) {
            if (current->left) {
                previous = current;
                current = current->left;
            } else {
                std::cout << "Node not found: " << value << "\n";
                return;
            }
        } else if (value > current->value) {
            if (current->right) {
                previous = current;
                current = current->right;
            } else {
                std::cout << "Node not found: " << value << "\n";
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
                Node* m = this->maximumNode(current->left);

                if (m->parent != current) {
                    this->transplant(m, m->left);
                    m->left = current->left;
                    if (m->left) m->left->parent = m;
                }

                this->transplant(current, m);

                m->right = current->right;
                if (m->right) m->right->parent = m;
            }
            delete current;
            updateHeights(previous);
            balance(previous);
            return;
        }
    }
}