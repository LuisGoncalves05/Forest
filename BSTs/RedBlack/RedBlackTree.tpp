#pragma once

#include <iostream>

template <typename T> template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
RedBlackTree<T>::RedBlackTree(Iter begin, Iter end) : RedBlackTree() {
    this->insertRange(begin, end, [&](T value) {this->insert(value);});
}

template <typename T> 
void RedBlackTree<T>::insert(const T &value, Node *node) {
    Node *current = node == nullptr ? this->root : node;
    if (current == nullptr) {
        this->root = new Node(value, nullptr, nullptr, nullptr, Node::Color::BLACK);
        return;
    }

    Node *inserted = nullptr;

    while (inserted == nullptr) {
        if (value < current->value) {
            if (current->left != nullptr) {
                current = current->left;
            } else {
                inserted = current->left = new Node(value, current, nullptr, nullptr);
            }
        } else if (value > current->value) {
            if (current->right != nullptr) {
                current = current->right;
            } else {
                inserted = current->right = new Node(value, current, nullptr, nullptr);
            }
        } else {
            std::cout << "Already have an equal node: " << value << "\n";
            return;
        }
    }
    fixInsert(inserted);
}

template <typename T>
void RedBlackTree<T>::fixInsert(Node *node) {
    while (getColor(getParent(node)) == Node::Color::RED) {
        Node *parent = getParent(node);
        Node *grandparent = getParent(parent);

        Node *uncle = (parent == getLeft(grandparent))
                      ? getRight(grandparent)
                      : getLeft(grandparent);

        if (getColor(uncle) == Node::Color::RED) {
            // Case 1: Red Uncle
            setColor(parent, Node::Color::BLACK);
            setColor(uncle, Node::Color::BLACK);
            setColor(grandparent, Node::Color::RED);
            node = grandparent; // Move up the tree
        } else {
            // Case 2: Triangle (Left-Right or Right-Left)
            if (node == getRight(parent) && parent == getLeft(grandparent)) {
                node = parent;
                this->leftRotate(node);
            } else if (node == getLeft(parent) && parent == getRight(grandparent)) {
                node = parent;
                this->rightRotate(node);
            }

            // Case 3: Line (Left-Left or Right-Right)
            parent = getParent(node);
            grandparent = getParent(parent);

            setColor(parent, Node::Color::BLACK);
            setColor(grandparent, Node::Color::RED);

            if (node == getLeft(parent) && parent == getLeft(grandparent)) {
                this->rightRotate(grandparent);
            } else {
                this->leftRotate(grandparent);
            }
            break;
        }
    }

    setColor(this->root, Node::Color::BLACK); // Ensure root is always black
}

template <typename T> 
void RedBlackTree<T>::remove(const T &value, Node *node) {
    if (this->root == nullptr) {
        std::cout << "Node not found: " << value << "\n";
        return;
    }

    Node *z = (node == nullptr) ? this->root : node;

    while (true) {
        if (value < getValue(z)) {
            if (getLeft(z) != nullptr) {
                z = getLeft(z);
            } else {
                std::cout << "Node not found: " << value << "\n";
                break;
            }
        } else if (value > getValue(z)) {
            if (getRight(z) != nullptr) {
                z = getRight(z);
            } else {
                std::cout << "Node not found: " << value << "\n";
                break;
            }
        } else {
            Node *y = z;
            Node *x = nullptr;
            Node *xParent = nullptr;
            typename Node::Color yOriginalColor = getColor(y);

            if (getLeft(z) == nullptr) {
                x = getRight(z);
                xParent = getParent(z);
                transplant(z, getRight(z));
            } else if (getRight(z) == nullptr) {
                x = getLeft(z);
                xParent = getParent(z);
                transplant(z, getLeft(z));
            } else {
                y = this->maximumNode(getLeft(z));
                yOriginalColor = getColor(y);
                x = getLeft(y);

                if (getParent(y) == z) {
                    xParent = y;
                    if (x != nullptr) {
                        setParent(x, y);
                    }
                } else {
                    xParent = getParent(y);
                    transplant(y, getLeft(y));
                    setLeft(y, getLeft(z));
                    if (getLeft(y) != nullptr) {
                        setParent(getLeft(y), y);
                    }
                }

                transplant(z, y);
                setRight(y, getRight(z));
                if (getRight(y) != nullptr) {
                    setParent(getRight(y), y);
                }
                setColor(y, getColor(z));
            }

            delete z;

            // If the removed node was black, fix double-black
            if (yOriginalColor == Node::Color::BLACK) {
                fixRemove(x, xParent);
            }
            break;
        }
    }
}

template <typename T> //val null
void RedBlackTree<T>::transplant(Node *u, Node *v) {
    if (getParent(u) == nullptr) {
        this->root = v;
    } else if (u == getLeft(getParent(u))) {
        setLeft(getParent(u), v);
    } else {
        setRight(getParent(u), v);
    }
    if (v != nullptr) {
        setParent(v, getParent(u));
    }
}

template <typename T>
void RedBlackTree<T>::fixRemove(Node *x, Node *xParent) {
    while (x != this->root && getColor(x) == Node::Color::BLACK) {
        if (x == getLeft(xParent)) {
            Node *w = getRight(xParent);

            if (getColor(w) == Node::Color::RED) { // Case 1
                setColor(w, Node::Color::BLACK);
                setColor(xParent, Node::Color::RED);
                this->leftRotate(xParent);
                w = getRight(xParent);
            }

            if (getColor(getLeft(w)) == Node::Color::BLACK &&
                getColor(getRight(w)) == Node::Color::BLACK) { // Case 2
                setColor(w, Node::Color::RED);
                x = xParent;   // bubble up
                xParent = getParent(x);
            } else {
                if (getColor(getRight(w)) == Node::Color::BLACK) { // Case 3
                    setColor(getLeft(w), Node::Color::BLACK);
                    setColor(w, Node::Color::RED);
                    this->rightRotate(w);
                    w = getRight(xParent);
                }
                // Case 4
                setColor(w, getColor(xParent));
                setColor(xParent, Node::Color::BLACK);
                setColor(getRight(w), Node::Color::BLACK);
                this->leftRotate(xParent);
                x = this->root; // terminate
            }
        } else {
            Node *w = getLeft(xParent);

            if (getColor(w) == Node::Color::RED) { // Case 1
                setColor(w, Node::Color::BLACK);
                setColor(xParent, Node::Color::RED);
                this->rightRotate(xParent);
                w = getLeft(xParent);
            }

            if (getColor(getRight(w)) == Node::Color::BLACK &&
                getColor(getLeft(w)) == Node::Color::BLACK) { // Case 2
                setColor(w, Node::Color::RED);
                x = xParent;   // bubble up
                xParent = getParent(x);
            } else {
                if (getColor(getLeft(w)) == Node::Color::BLACK) { // Case 3
                    setColor(getRight(w), Node::Color::BLACK);
                    setColor(w, Node::Color::RED);
                    this->leftRotate(w);
                    w = getLeft(xParent);
                }
                // Case 4
                setColor(w, getColor(xParent));
                setColor(xParent, Node::Color::BLACK);
                setColor(getLeft(w), Node::Color::BLACK);
                this->rightRotate(xParent);
                x = this->root; // terminate
            }
        }
    }

    setColor(x, Node::Color::BLACK);
}

template <typename T>
RedBlackTreeNode<T> *RedBlackTree<T>::getParent(Node *node) {
    return node ? node->parent : nullptr;
}

template <typename T>
void RedBlackTree<T>::setParent(Node *node, Node *parent) {
    if (node != nullptr) {
        node->parent = parent;
    }
}

template <typename T>
RedBlackTreeNode<T> *RedBlackTree<T>::getLeft(Node *node) {
    return node ? node->left : nullptr;
}

template <typename T>
void RedBlackTree<T>::setLeft(Node *node, Node *left) {
    if (node != nullptr) {
        node->left = left;
    }
}

template <typename T>
RedBlackTreeNode<T> *RedBlackTree<T>::getRight(Node *node) {
    return node ? node->right : nullptr;
}

template <typename T>
void RedBlackTree<T>::setRight(Node *node, Node *right) {
    if (node != nullptr) {
        node->right = right;
    }
}

template <typename T>
RedBlackTreeNode<T>::Color RedBlackTree<T>::getColor(Node *node) {
    return node ? node->color : Node::Color::BLACK;
}

template <typename T>
void RedBlackTree<T>::setColor(Node *node, Node::Color color) {
    if (node != nullptr) {
        node->color = color;
    }
}

template <typename T>
T RedBlackTree<T>::getValue(Node *node) {
    return node ? node->value : T{};
}

template <typename T>
void RedBlackTree<T>::setValue(Node *node, const T &value) {
    if (node != nullptr) {
        node->value = value;
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const RedBlackTree<T> &tree) {
    os << "Tree(root: ";
    if (tree.root == nullptr) {
        os << "nil";
    } else {
        os << *tree.root;
    }

    os << ")";
    return os;
}