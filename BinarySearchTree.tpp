#pragma once

#include <iostream>

template <typename Node> template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, typename BinarySearchTree<Node>::valueType>
BinarySearchTree<Node>::BinarySearchTree(Iter begin, Iter end) {
    insertRange(begin, end, [&](typename BinarySearchTree<Node>::valueType &value) {this->insert(value);});
}

template <typename Node>
template <std::input_iterator Iter, typename Inserter> requires std::same_as<std::iter_value_t<Iter>, typename BinarySearchTree<Node>::valueType>
void BinarySearchTree<Node>::insertRange(Iter begin, Iter end, Inserter inserter) {
    for (; begin != end; ++begin)
        inserter(*begin);
}


template <typename Node>
BinarySearchTree<Node>::~BinarySearchTree() {
    deleteSubTree(root);
}

template <typename Node>
void BinarySearchTree<Node>::deleteSubTree(Node *node) {
    if (node == nullptr) return;

    Node *l = node->left, *r = node->right;
    delete node;
    deleteSubTree(l);
    deleteSubTree(r);
}



template <typename Node>
void BinarySearchTree<Node>::insert(valueType &value, Node *node) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }

    Node *current = node == nullptr ? root : node;
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
            std::cout << "Already have an equal node: " << value << "\n";
            return;
        }
    }
}

template <typename Node>
void BinarySearchTree<Node>::remove(valueType &value, Node *node) {
    Node *previous = nullptr;
    Node *current = node == nullptr ? root : node;
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
                if (current == root) {
                    root = nullptr;
                } else if (current == previous->left) {
                    previous->left = nullptr;
                } else if (current == previous->right) {
                    previous->right = nullptr;
                }
            } else if ((!current->left && current->right) || (current->left && !current->right)) { // 1 child
                Node *child = current->left ? current->left : current->right;
                if (current == root) {
                    root = child;
                    root->parent = nullptr;
                } else {
                    if (current == previous->left) {
                        previous->left = child;
                    } else if (current == previous->right) {
                        previous->right = child;
                    }
                    child->parent = previous;
                }
            } else { // 2 children
                valueType &m = minimum(current->right);
                remove(m, current);

                Node *min = new Node(m, previous);
                min->left = current->left;
                min->right = current->right;
                current->left->parent = min;
                current->right->parent = min;

                if (current == root) {
                    root = min;
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

template <typename Node>
typename BinarySearchTree<Node>::valueType &BinarySearchTree<Node>::minimum(Node *node) {
    Node *m = node == nullptr ? root : node;
    if (m == nullptr) {
        throw std::logic_error("Can't find minimum of empty tree.");
    }

    while (m->left) {
        m = m->left;
    }
    return m->value;
}

template <typename Node>
typename BinarySearchTree<Node>::valueType &BinarySearchTree<Node>::maximum(Node *node) {
    Node *m = node == nullptr ? root : node;
    if (m == nullptr) {
        throw std::logic_error("Can't find maximum of empty tree.");
    }
    while (m->right) {
        m = m->right;
    }
    return m->value;
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