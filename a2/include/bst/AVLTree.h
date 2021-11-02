//
// Created by Xianglu on 2/17/20.
//

#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include "AVLNode.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

template<class Object>
class AVLTree {
private:
    AVLNode <Object> * root;
    AVLNode <Object> * find(AVLNode<Object> *node, Object element);
    AVLNode <Object> * insert(AVLNode<Object> *node, Object newElement);
    AVLNode <Object> * findMin(AVLNode<Object> *node);
    AVLNode <Object> * findMax(AVLNode<Object> *node);
    AVLNode <Object> * remove(AVLNode<Object> *node, Object element);
    AVLNode <Object> * rotateLeftChild(AVLNode<Object> *nodeA);
    AVLNode <Object> * rotateRightChild(AVLNode<Object> *nodeA);
    AVLNode <Object> * doubleRotateLeftChild(AVLNode<Object> *nodeA);
    AVLNode <Object> * doubleRotateRightChild(AVLNode<Object> *nodeA);
    AVLNode <Object> * Balance(AVLNode<Object> *node);
    void printTree(AVLNode<Object> *node, string prefix, int level);
public:
    explicit AVLTree(Object element);
    AVLNode<Object> *find(Object element);
    AVLNode<Object> * findMin();
    AVLNode<Object> * findMax();
    void insert(Object element);
    void printTree();
    void remove(Object element);
    virtual ~AVLTree();
};


template<class Object>
AVLNode<Object> *AVLTree<Object>::find(Object element) {
    return find(this->root, element);
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::find(AVLNode<Object> *node, Object element) {
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
void AVLTree<Object>::printTree() {
    printTree(this->root, "R:", 0);
}

template<class Object>
void AVLTree<Object>::printTree(AVLNode<Object> *node, string prefix, int level) {

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
AVLTree<Object>::AVLTree(Object element) {
    root = new AVLNode<Object>(element);
}

template<class Object>
void AVLTree<Object>::insert(Object element) {
    this->insert(root, element);
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::insert(AVLNode<Object> *node, Object newElement) {
    if (node == nullptr)
        return new AVLNode<Object>(newElement);
    else if (node->element < newElement)
        node->right = insert(node->right, newElement);
    else if (node->element > newElement)
        node->left = insert(node->left, newElement);
    //update height and height diff
    node->updateHeightInfo();
    //return the node balanced
    return Balance(node);

}

template<class Object>
AVLNode<Object> *AVLTree<Object>::rotateLeftChild(AVLNode<Object> *nodeA) {
    AVLNode<Object> *nodeB = nodeA->left;
    nodeA->left = nodeB->right;
    nodeB->right = nodeA;
    nodeA->updateHeightInfo();
    nodeB->updateHeightInfo();
    return nodeB;
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::rotateRightChild(AVLNode<Object> *nodeA) {
    AVLNode<Object> *nodeB = nodeA->right;
    nodeA->right = nodeB->left;
    nodeB->left = nodeA;
    nodeA->updateHeightInfo();
    nodeB->updateHeightInfo();
    return nodeB;
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::doubleRotateLeftChild(AVLNode<Object> *nodeA){
    AVLNode<Object> *nodeB = nodeA->left;
    nodeA->left = rotateRightChild(nodeB);
    return rotateLeftChild(nodeA);
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::doubleRotateRightChild(AVLNode<Object> *nodeA){
    AVLNode<Object> *nodeB = nodeA->right;
    nodeA->right = rotateLeftChild(nodeB);
    return rotateRightChild(nodeA);
}

static const int ALLOWED_IMBALANCE = 1;
template<class Object>
AVLNode<Object> *AVLTree<Object>::Balance(AVLNode<Object> *node) {
    if (node == nullptr)
        return nullptr;
    int heightDiff = node->heightDiff;
    //no imbalance
    if (abs(heightDiff) <= ALLOWED_IMBALANCE)return node;
    //there is imbalance
    if (heightDiff < 0) {//there is an imbalance in the left child
        //case1 single
        if (node->left->left->height >= node->left->right->height)
            node = rotateLeftChild(node);
        else
            //case 2 double
            node = doubleRotateLeftChild(node);
    } else {//there is an imbalance in the right child
        if (node->right -> right != nullptr and node->right->left != nullptr) {
            // case4 single
            if (node->right->right->height >= node->right->left->height)
                node = rotateRightChild(node);
            else
                //case 3 double
                node = doubleRotateRightChild(node);
        }
        else if (node->right->right != nullptr and node ->right->left == nullptr){
            node = rotateRightChild(node);
        }
    }
    //update height and height diff
    node->updateHeightInfo();
    return node;
}



template<class Object>
AVLNode<Object> *AVLTree<Object>::findMin() {
    return findMin(this->root);
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::findMax() {
    return findMax(this->root);
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::findMin(AVLNode<Object> *node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return findMin(node->left);
}

template<class Object>
AVLNode<Object> *AVLTree<Object>::findMax(AVLNode<Object> *node) {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return findMax(node->right);
}

template<class Object>
void AVLTree<Object>::remove(Object element) {
    this->root = this->remove(this->root, element);
}




template<class Object>
AVLNode<Object> *AVLTree<Object>::remove(AVLNode<Object> *node, Object element) {
    //nothing to do here
    if (node == nullptr) return nullptr;
    //if node < element --> the element is in the right subtree, remove it
    if (node->element < element)
        node->right = remove(node->right, element);
    //if node > element --> the element is in the left subtree, remove it
    else if (node->element > element)
        node->left = remove(node->left, element); //if node == element then remove it
    else {
    //temporal variable
        AVLNode<Object> *temp = nullptr;
    //case: the node has two children
    //approach: replace the node with the min element in the right subtree and then remove the min
        if (node->left != nullptr && node->right != nullptr) {
            temp = findMin(node->right);
            node->element = temp->element;
            node->right = remove(node->right, temp->element);
        } else {
    //if no left child, then node should be the right child, otherwise, it should be left one
            if (node->left == nullptr) temp = node->right; else temp = node->left;
            delete (node);
            node = temp;
        }
    }
    //update height and height diff
    if (node != nullptr)
        node->updateHeightInfo();
    //return the node balanced
    return Balance(node);
}

template<class Object>
AVLTree<Object>::~AVLTree() {
    delete this->root;
}


#endif //TREES_AVLTREE_H
