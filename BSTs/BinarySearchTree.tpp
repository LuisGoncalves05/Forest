#pragma once

#include <iostream>

template <typename Node> template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, typename BinarySearchTree<Node>::valueType>
BinarySearchTree<Node>::BinarySearchTree(Iter begin, Iter end) : BinarySearchTree() {
    insertRange(begin, end, [&](const typename BinarySearchTree<Node>::valueType &value) {this->insert(value);});
}

template <typename Node>
template <std::input_iterator Iter, typename Inserter> requires std::same_as<std::iter_value_t<Iter>, typename BinarySearchTree<Node>::valueType>
void BinarySearchTree<Node>::insertRange(Iter begin, Iter end, Inserter inserter) {
    for (; begin != end; ++begin)
        inserter(*begin);
}

template <typename Node>
void BinarySearchTree<Node>::leftRotate(Node *x) {
    Node *p = x->parent;
    Node *y = x->right;

    y->parent = p;
    if (p == nullptr) {
        this->root = y;
    } else if (x == p->left) {
        p->left = y;
    } else {
        p->right = y;
    }
    x->parent = y;

    x->right = y->left;
    if (x->right) x->right->parent = x;
    y->left = x;
}

template <typename Node>
void BinarySearchTree<Node>::rightRotate(Node *y) {
    Node *p = y->parent;
    Node *x = y->left;

    x->parent = p;
    if (p == nullptr) {
        this->root = x;
    } else if (y == p->left) {
        p->left = x;
    } else {
        p->right = x;
    }
    y->parent = x;

    y->left = x->right;
    if (y->left) y->left->parent = y;
    x->right = y;
}

template <typename Node>
BinarySearchTree<Node>::~BinarySearchTree() {
    deleteSubTree(root);
}

template <typename Node>
void BinarySearchTree<Node>::deleteSubTree(Node *node) {
    if (node == nullptr) return;

    Node *l = node->left, *r = node->right;
    deleteSubTree(l);
    deleteSubTree(r);
    delete node;
}

template <typename Node>
void BinarySearchTree<Node>::insert(const valueType &value) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }

    Node *current = root;
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
void BinarySearchTree<Node>::remove(const valueType &value) {
    Node *previous = nullptr;
    Node *current = root;
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
            return;
        }
    }
}

template <typename Node>
Node *BinarySearchTree<Node>::minimumNode(Node* node) {
    if (!node) return nullptr;

    Node* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

template <typename Node>
const typename BinarySearchTree<Node>::valueType &BinarySearchTree<Node>::minimum(Node* node) {
    const Node *m = this->minimumNode(node);
    if (m == nullptr) {
        throw std::logic_error("Can't find minimum of empty tree.");
    }

    return m->value;
}

template <typename Node>
const typename BinarySearchTree<Node>::valueType &BinarySearchTree<Node>::minimum() {
    return this->minimum(this->root);
}

template <typename Node>
Node *BinarySearchTree<Node>::maximumNode(Node* node) {
    if (!node) return nullptr;

    Node* current = node;
    while (current->right) {
        current = current->right;
    }
    return current;
}

template <typename Node>
const typename BinarySearchTree<Node>::valueType &BinarySearchTree<Node>::maximum(Node* node) {
    const Node *m = this->maximumNode(node);
    if (m == nullptr) {
        throw std::logic_error("Can't find minimum of empty tree.");
    }

    return m->value;
}

template <typename Node>
const typename BinarySearchTree<Node>::valueType &BinarySearchTree<Node>::maximum() {
    return this->maximum(this->root);
}

template <typename Node>
bool BinarySearchTree<Node>::find(const valueType &value) {
    Node *current = root;
    if (current == nullptr) return false;

    while (value != current->value) {
        if (value < current->value) {
            if (current->left) {
                current = current->left;
            } else {
                return false;
            }
        } else if (value > current->value) {
            if (current->right) {
                current = current->right;
            } else {
                return false;
            }
        }
    }
    return true;
}

template <typename Node>
int BinarySearchTree<Node>::maxHeight() {
    return maxHeight(root);
}

template <typename Node>
int BinarySearchTree<Node>::maxHeight(Node *node) {
    if (node == nullptr) return 0;

    int leftHeight  = maxHeight(node->left);
    int rightHeight = maxHeight(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

template <typename Node>
void BinarySearchTree<Node>::transplant(Node *u, Node *v) {
    if (u->parent == nullptr) {
        this->root = v;
    } else if (u->parent->left == u) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
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