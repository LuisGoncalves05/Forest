#pragma once

#include "BinarySearchTree.hpp"

template <typename T>
using BST = BinarySearchTree<BinarySearchTreeNode<T>>;

#include "AvlTree.hpp"

template <typename T>
using AVL = AvlTree<T>;
