#pragma once

#include <iostream>

template <typename T>
void AvlTree<T>::insert(T &value, Node *node) {
    if (this->root == nullptr) {
        this->root = new Node(value);
        return;
    }

    Node *current = node == nullptr ? this->root : node;
    while (true) {
        if (value < current->value) {
            if (current->left) {
                current = current->left;
            } else {
                current->left = new Node(value, current);
                return;
            }
        } else if (value > current->value) {
            if (current->right) {
                current = current->right;
            } else {
                current->right = new Node(value, current);
                return;
            }
        } else {
            std::cout << "Already have an equal node: " << node->value << "\n";
            return;
        }
    }
}

template <typename T>
void AvlTree<T>::remove(T &value, Node *node) {
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
                T &m = this->minimum(current->right);
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
}

template <typename T>
void AvlTree<T>::updateHeights(Node *node) {
    if (node == nullptr) return;

    int hl = node->left ? node->left->height : 0;
    int hr = node->right ? node->right->height : 0;
    int newHeight = std::max(hl, hr) + 1;

    if (node->height != newHeight) {
        node->height = newHeight;
        updateHeights(node->parent);
    }
}

template <typename T>
void AvlTree<T>::balance(Node *node) {
    if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr) {
        return;
    }

    int parentParentBalance = node->parent->parent->getBalance();
    int parentBalance = node->parent->getBalance();

    if (parentParentBalance == 2) {
        if (parentBalance == 1) {
            leftLeft(node);
        } else { // -1
            leftRight(node);
        }
    } else if (parentParentBalance == -2) {
        if (parentBalance == 1) {
            rightLeft(node);
        } else { // -1
            rightRight(node);
        }
    }
}

template <typename T>
void AvlTree<T>::leftRotate(Node *node) {
    Node *x = node->parent;
    Node *p = x->parent;

    x->right = node->left;
    x->parent = node;
    node->left = x;
    node->parent = p;

    updateHeights(x);
}

template <typename T>
void AvlTree<T>::rightRotate(Node *node) {
    Node *y = node->parent;
    Node *p = y->parent;

    y->left = node->right;
    y->parent = node;
    node->right = y;
    node->parent = p;

    updateHeights(y);
}

template <typename T>
void AvlTree<T>::leftLeft(Node *node) {
    rightRotate(node->parent);
}

template <typename T>
void AvlTree<T>::leftRight(Node *node) {
    leftRotate(node);
}

template <typename T>
void AvlTree<T>::rightLeft(Node *node) {
    rightRotate(node);
}

template <typename T>
void AvlTree<T>::rightRight(Node *node) {
    leftRotate(node->parent);
}