#pragma once

#include "BSTs/BinarySearchTree.hpp"

template <typename T>
using BST = BinarySearchTree<BinarySearchTreeNode<T>>;

#include "BSTs/AVL/AvlTree.hpp"

template <typename T>
using AVL = AvlTree<T>;

#include "BSTs/RedBlack/RedBlackTree.hpp"

template <typename T>
using RBT = RedBlackTree<T>;