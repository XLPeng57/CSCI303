//
// Created by ojcch on 2/3/2020.
//

#ifndef TREES_BINARYSEARCHTREE_H
#define TREES_BINARYSEARCHTREE_H

#include "TreeNode.h"
#include <string>


using namespace std;

template<class Object>
class BinarySearchTree {
private:
    TreeNode<Object> *root;

    TreeNode<Object> *find(TreeNode<Object> *node, Object element);
    TreeNode<Object> * insert(TreeNode<Object> *node, Object newElement);
    TreeNode<Object> * findMin(TreeNode<Object> *node);
    TreeNode<Object> * findMax(TreeNode<Object> *node);
    TreeNode<Object> * remove(TreeNode<Object> *node, Object element);
    void printTree(TreeNode<Object> *node, string prefix, int level);
public:
    explicit BinarySearchTree(Object element);
    TreeNode<Object> *find(Object element);
    TreeNode<Object> * findMin();
    TreeNode<Object> * findMax();
    void insert(Object element);
    void printTree();
    void  remove(Object element);

    virtual ~BinarySearchTree();

};


#include "bst/BinarySearchTree.h"


# include <iostream>

template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::find(Object element) {
    return find(this->root, element);
}

template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::find(TreeNode<Object> *node, Object element) {
    if (node == nullptr)
        return nullptr;
    else if (node->element == element)
        return node;
    else if (node->element < element)
        return find(node->right, element);
    else
        return find(node->left, element);
}

template<class Object>
BinarySearchTree<Object>::BinarySearchTree(Object element) {
    root = new TreeNode<Object>(element);
}

template<class Object>
void BinarySearchTree<Object>::insert(Object element) {
    this->insert(root, element);
}

template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::insert(TreeNode<Object> *node, Object newElement) {
    if (node == nullptr)
        return new TreeNode<Object>(newElement);
    else if (node->element < newElement)
        node->right = insert(node->right, newElement);
    else if (node->element > newElement)
        node->left = insert(node->left, newElement);

    return node;
}

template<class Object>
void BinarySearchTree<Object>::printTree() {
    printTree(this->root, "R:", 0);
}

template<class Object>
void BinarySearchTree<Object>::printTree(TreeNode<Object> *node, string prefix, int level) {

    if (node == nullptr) return;
    string levelStr;
    for (int i = 0; i < level; ++i) {
        levelStr.append("  ");
    }
    cout << levelStr << prefix << node->element << endl;
    printTree(node->left, "Lf:", level + 1);
    printTree(node->right, "Rg:", level + 1);

}

template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::findMin() {
    return findMin(this->root);
}

template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::findMax() {
    return findMax(this->root);
}


template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::findMin(TreeNode<Object> *node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return findMin(node->left);
}

template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::findMax(TreeNode<Object> *node) {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return findMax(node->right);
}

template<class Object>
void BinarySearchTree<Object>::remove(Object element) {
    this->root = this->remove(this->root, element);
}

template<class Object>
TreeNode<Object> *BinarySearchTree<Object>::remove(TreeNode<Object> *node, Object element) {
    //nothing to do here
    if (node == nullptr) return nullptr;
    //if node < element --> the element is in the right subtree, remove it
    if (node->element < element)
        node->right = remove(node->right, element);
        //if node > element --> the element is in the left subtree, remove it
    else if (node->element > element)
        node->left = remove(node->left, element);
        //if node == element then remove it
    else {
        //temporal variable
        TreeNode<Object> *temp = nullptr;
        //case: the node has two children
        //approach: replace the node with the min element in the right subtree and then remove the min
        if (node->left != nullptr && node->right != nullptr) {
            temp = findMin(node->right);
            node->element = temp->element;
            node->right = remove(node->right, temp->element);
        } else {
            //if no left child, then node should be the right child, otherwise, it should be left one
            if (node->left == nullptr) {
                temp = node->right;
                node->right = nullptr;
            } else {
                temp = node->left;
                node->left = nullptr;
            }
            delete (node);
            node = temp;
        }
    }
    return node;
}

template<class Object>
BinarySearchTree<Object>::~BinarySearchTree() {
    delete this->root;
}

#endif //TREES_BINARYSEARCHTREE_H
