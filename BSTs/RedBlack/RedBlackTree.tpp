#pragma once

#include <iostream>

template <typename T>
RedBlackTree<T>::RedBlackTree() {
    this->root = Node::nil;
}

template <typename T>
void RedBlackTree<T>::deleteSubTree(Node *node) {
    if (node == Node::nil || node == nullptr) return;

    Node *l = node->left, *r = node->right;
    deleteSubTree(l);
    deleteSubTree(r);
    delete node;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    this->deleteSubTree(this->root);
    this->root = nullptr; // Bst delete will run after so root needs to be nullptr
}

template <typename T>
void RedBlackTree<T>::leftRotate(Node *x) {
    Node *p = x->parent;
    Node *y = x->right;

    y->parent = p;
    if (p == Node::nil) {
        this->root = y;
    } else if (x == p->left) {
        p->left = y;
    } else {
        p->right = y;
    }
    x->parent = y;

    x->right = y->left;
    if (x->right != Node::nil) {
        x->right->parent = x;
    }
    y->left = x;
}

template <typename T>
void RedBlackTree<T>::rightRotate(Node *y) {
    Node *p = y->parent;
    Node *x = y->left;

    x->parent = p;
    if (p == Node::nil) {
        this->root = x;
    } else if (y == p->left) {
        p->left = x;
    } else {
        p->right = x;
    }
    y->parent = x;

    y->left = x->right;
    if (y->left != Node::nil) {
        y->left->parent = y;
    }
    x->right = y;
}

template <typename T> template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
RedBlackTree<T>::RedBlackTree(Iter begin, Iter end) : RedBlackTree() {
    this->insertRange(begin, end, [&](T &value) {this->insert(value);});
}

template <typename T> 
void RedBlackTree<T>::insert(const T &value, Node *node) {
    // Inserts in root if it is nil, even if node is not nullptr, which is not possible if all is correct but who knows
    Node *current = node == nullptr ? this->root : node;
    if (this->root == Node::nil) {
        this->root = new Node(value, Node::nil, Node::nil, Node::nil, Node::Color::BLACK);
        return;
    }

    Node *inserted = nullptr;

    while (inserted == nullptr) {
        if (value < current->value) {
            if (current->left != Node::nil) {
                current = current->left;
            } else {
                inserted = current->left = new Node(value, current, Node::nil, Node::nil);
            }
        } else if (value > current->value) {
            if (current->right != Node::nil) {
                current = current->right;
            } else {
                inserted = current->right = new Node(value, current, Node::nil, Node::nil);
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
    while (node->parent->color == Node::Color::RED) {
        Node *uncle = (node->parent == node->parent->parent->left)
                      ? node->parent->parent->right
                      : node->parent->parent->left;

        if (uncle->color == Node::Color::RED) { // Case 1: Red Uncle
            node->parent->color = Node::Color::BLACK;
            uncle->color = Node::Color::BLACK;
            node->parent->parent->color = Node::Color::RED;
            node = node->parent->parent; // Move up the tree
        } else { // Black Uncle
            // Case 2: Triangle (Left-Right or Right-Left)
            if (node == node->parent->right && node->parent == node->parent->parent->left) {
                this->leftRotate(node->parent);
                node = node->parent;
            } else if (node == node->parent->left && node->parent == node->parent->parent->right) {
                this->rightRotate(node->parent);
                node = node->parent;
            }

            // Case 3: Line (Left-Left or Right-Right)
            node->parent->color = Node::Color::BLACK;
            node->parent->parent->color = Node::Color::RED;
            if (node == node->parent->left && node->parent == node->parent->parent->left) {
                this->rightRotate(node->parent->parent);
            } else {
                this->leftRotate(node->parent->parent);
            }
            break;
        }
    }

    this->root->color = Node::Color::BLACK; // Ensure root is always black
}


template <typename T> 
void RedBlackTree<T>::remove(const T &value, Node *node) {
    if (this->root == nullptr || this->root == Node::nil) {
        std::cout << "Node not found: " << value << "\n";
        return;
    }
    Node *z = node == nullptr ? this->root : node;

    while (true) {
        if (value < z->value) {
            if (z->left != Node::nil) {
                z = z->left;
            } else {
                std::cout << "Node not found: " << value << "\n";
                break;
            }
        } else if (value > z->value) {
            if (z->right != Node::nil) {
                z = z->right;
            } else {
                std::cout << "Node not found: " << value << "\n";
                break;
            }
        } else {
            Node *y = z;
            Node *x = nullptr;
            Node *xParent = nullptr;
            typename Node::Color yOriginalColor = y->color;

            if (z->left == Node::nil) {
                x = z->right;
                xParent = z->parent;
                transplant(z, z->right);
            } else if (z->right == Node::nil) {
                x = z->left;
                xParent = z->parent;
                transplant(z, z->left);
            } else {
                y = this->maximumNode(z->left);
                yOriginalColor = y->color;
                x = y->left;
                
                if (y->parent == z) {
                    xParent = y;
                    if (x != Node::nil) {
                        x->parent = y;
                    }
                } else {
                    xParent = y->parent;
                    transplant(y, y->left);
                    y->left = z->left;
                    if (y->left != Node::nil) {
                        y->left->parent = y;
                    }
                }

                transplant(z, y);
                y->right = z->right;
                if (y->right != Node::nil) {
                    y->right->parent = y;
                }
                y->color = z->color;
            }
            delete z;

            // 4. If the removed node was black, fix double-black
            if (yOriginalColor == Node::Color::BLACK) {
                fixRemove(x, xParent);
            }

            break;
        }
    }
}

template <typename T>
void RedBlackTree<T>::transplant(Node *u, Node *v) {
    if (u->parent == Node::nil) {
        this->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != Node::nil) {
        v->parent = u->parent;
    }
}

template <typename T>
void RedBlackTree<T>::fixRemove(Node *x, Node *xParent) {
    while (x != this->root && x->color == Node::Color::BLACK) {
        if (x == xParent->left) {
            Node *w = xParent->right;

            if (w->color == Node::Color::RED) { // Case 1
                w->color = Node::Color::BLACK;
                xParent->color = Node::Color::RED;
                this->leftRotate(xParent);
                w = xParent->right;
            }

            if (w->left->color == Node::Color::BLACK &&
                w->right->color == Node::Color::BLACK) { // Case 2
                w->color = Node::Color::RED;
                x = xParent;   // bubble up
                xParent = x->parent;
            } else {
                if (w->right->color == Node::Color::BLACK) { // Case 3
                    w->left->color = Node::Color::BLACK;
                    w->color = Node::Color::RED;
                    this->rightRotate(w);
                    w = xParent->right;
                }
                // Case 4
                w->color = xParent->color;
                xParent->color = Node::Color::BLACK;
                w->right->color = Node::Color::BLACK;
                this->leftRotate(xParent);
                x = this->root; // terminate
            }
        } else {
            Node *w = xParent->left;

            if (w->color == Node::Color::RED) { // Case 1
                w->color = Node::Color::BLACK;
                xParent->color = Node::Color::RED;
                this->rightRotate(xParent);
                w = xParent->left;
            }

            if (w->right->color == Node::Color::BLACK &&
                w->left->color == Node::Color::BLACK) { // Case 2
                w->color = Node::Color::RED;
                x = xParent;   // bubble up
                xParent = x->parent;
            } else {
                if (w->left->color == Node::Color::BLACK) { // Case 3
                    w->right->color = Node::Color::BLACK;
                    w->color = Node::Color::RED;
                    this->leftRotate(w);
                    w = xParent->left;
                }
                // Case 4
                w->color = xParent->color;
                xParent->color = Node::Color::BLACK;
                w->left->color = Node::Color::BLACK;
                this->rightRotate(xParent);
                x = this->root; // terminate
            }
        }
    }

    x->color = Node::Color::BLACK;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const RedBlackTree<T> &tree) {
    os << "Tree(root: ";
    if (tree.root == RedBlackTreeNode<T>::nil) {
        os << "nil";
    } else {
        os << *tree.root;
    }

    os << ")";
    return os;
}


template <typename T>
RedBlackTreeNode<T> *RedBlackTree<T>::minimumNode(Node* node) {
    if (node == Node::nil) return Node::nil;

    Node* current = node;
    while (current->left != Node::nil) {
        current = current->left;
    }
    return current;
}


template <typename T>
const T &RedBlackTree<T>::minimum(Node* node) {
    const Node *m = this->minimumNode(node);
    if (m == Node::nil) {
        throw std::logic_error("Can't find minimum of empty tree.");
    }

    return m->value;
}

template <typename T>
const T &RedBlackTree<T>::minimum() {
    return this->minimum(this->root);
}

template <typename T>
RedBlackTreeNode<T> *RedBlackTree<T>::maximumNode(Node* node) {
    if (node == Node::nil) return Node::nil;

    Node* current = node;
    while (current->right != Node::nil) {
        current = current->right;
    }
    return current;
}

template <typename T>
const T &RedBlackTree<T>::maximum(Node* node) {
    const Node *m = this->maximumNode(node);
    if (m == Node::nil) {
        throw std::logic_error("Can't find minimum of empty tree.");
    }

    return m->value;
}

template <typename T>
const T &RedBlackTree<T>::maximum() {
    return this->maximum(this->root);
}

template <typename T>
bool RedBlackTree<T>::find(const T &value) {
    Node *current = this->root;
    if (current == Node::nil) return false;

    while (value != current->value) {
        if (value < current->value) {
            if (current->left != Node::nil) {
                current = current->left;
            } else {
                return false;
            }
        } else if (value > current->value) {
            if (current->right != Node::nil) {
                current = current->right;
            } else {
                return false;
            }
        }
    }
    return true;
}