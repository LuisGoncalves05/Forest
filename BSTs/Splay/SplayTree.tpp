#pragma once

template <typename T>
void SplayTree<T>::zig(Node *node) {
    this->rightRotate(node->parent);
}

template <typename T>
void SplayTree<T>::zag(Node *node) {
    this->leftRotate(node->parent);
}

template <typename T>
void SplayTree<T>::zigZig(Node *node) {
    zig(node->parent);
    zig(node);
}

template <typename T>
void SplayTree<T>::zigZag(Node *node) {
    zig(node);
    zag(node);
}

template <typename T>
void SplayTree<T>::zagZag(Node *node) {
    zag(node->parent);
    zag(node);
}

template <typename T>
void SplayTree<T>::zagZig(Node *node) {
    zag(node);
    zig(node);
}

template <typename T>
void SplayTree<T>::splay(Node *node) {
    while (node != this->root) {
        if (node->parent && node->parent->parent) {
            if (node == node->parent->right && node->parent == node->parent->parent->right){
                zagZag(node);
            } else if (node == node->parent->left && node->parent == node->parent->parent->left) {
                zigZig(node);
            } else if (node == node->parent->left && node->parent == node->parent->parent->right) {
                zigZag(node);
            } else {
                zagZig(node);
            }
        } else if (node->parent == this->root) {
            if (node == node->parent->right) {
                zag(node);
            } else {
                zig(node);
            }
        }
    }
}

template <typename T> template <std::input_iterator Iter> requires std::same_as<std::iter_value_t<Iter>, T>
SplayTree<T>::SplayTree(Iter begin, Iter end) : SplayTree() {
    this->insertRange(begin, end, [&](T value) {this->insert(value);});
}

template <typename T>
void SplayTree<T>::insert(const T &value) {
    if (this->root == nullptr) {
        this->root = new Node(value);
        return;
    }

    Node *inserted = nullptr;
    Node *current = this->root;
    while (inserted == nullptr) {
        if (value < current->value) {
            if (current->left) {
                current = current->left;
            } else {
                inserted = current->left = new Node(value, current);
            }
        } else if (value > current->value) {
            if (current->right) {
                current = current->right;
            } else {
                inserted = current->right = new Node(value, current);
            }
        } else {
            std::cout << "Already have an equal node: " << value << "\n";
            return;
        }
    }

    splay(inserted);
}

template <typename T>
void SplayTree<T>::remove(const T &value) {
    if (this->root == nullptr) {
        throw std::logic_error("Can't delete from an empty tree.");
        return;
    }

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
            splay(current);
            Node *l = current->left, *r = current->right;
            delete current;
            this->root = l;
            if (l == nullptr) {
                this->root = r;
                if (r) r->parent = nullptr;
            } else {
                l->parent = nullptr;
                if (r != nullptr) {
                    splay(this->maximumNode(l));
                    this->root->right = r;
                }
            }
            return;
        }
    }
}

template <typename T>
bool SplayTree<T>::find(const T &value) {
    Node *current = this->root;
    if (current == nullptr) return false;

    bool found = true;
    while (value != current->value) {
        if (value < current->value) {
            if (current->left) {
                current = current->left;
            } else {
                found = false;
                break;
            }
        } else if (value > current->value) {
            if (current->right) {
                current = current->right;
            } else {
                found = false;
                break;
            }
        }
    }
    splay(current);
    return found;
}
