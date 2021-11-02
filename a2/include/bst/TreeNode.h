//
// Created by ojcch on 2/3/2020.
//

#ifndef NEXTDATE_TREENODE_H
#define NEXTDATE_TREENODE_H
#include <string>
#include <iostream>

using namespace std;

template <class Object>
class TreeNode {
public:
    Object element;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(Object element);
    virtual ~TreeNode();
};

#include "bst/TreeNode.h"

template<class Object>
TreeNode<Object>::TreeNode(Object element) {
    this->element = element;
}

template<class Object>
TreeNode<Object>::~TreeNode() {
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
    left = nullptr;
    right = nullptr;
}




#endif //NEXTDATE_TREENODE_H
