//
// Created by Xianglu on 2/18/20.
//

#ifndef TREES_AVLNODE_H
#define TREES_AVLNODE_H

#include <string>
#include <iostream>
//#include "bst/AVLNode.h"

using namespace std;

template <class Object>
class AVLNode {

//private:
    //int updateHeightInfo(AVLNode<Object> *node);
public:
    Object element;
    explicit AVLNode(Object element);
    virtual ~AVLNode();
    int height;
    int heightDiff;
    AVLNode * left = nullptr;
    AVLNode * right = nullptr;
    void updateHeightInfo();
    //AVLNode <Object> * getHeightDiff(AVLNode<Object> *node)
};



template<class Object>
AVLNode<Object>::AVLNode(Object element) {
    this->element = element;
    height = 0;
    heightDiff = 0;
}


template<class Object>
AVLNode<Object>::~AVLNode() {
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
    left = nullptr;
    right = nullptr;
}

/*template<class Object>
void AVLNode<Object> ::updateHeightInfo(){
    updateHeightInfo(this);
}*/

template<class Object>
void AVLNode<Object>::updateHeightInfo() {
    if (this == nullptr) {
        this->height = -1;
        this->heightDiff = 0;
    }
    else {
        if (this->left == nullptr and this->right == nullptr) {
            this->height = 1;
            this->heightDiff = 0;
        }
        else if (this->right == nullptr and this->left != nullptr ){
            this->height = this->left->height + 1;
            this->heightDiff = -(this->left->height);
        }
        else if (this->left == nullptr and this->right != nullptr){
            this -> height = this->right->height + 1;
            this->heightDiff =  this->right->height;
        }
        else if (this->left != nullptr and this->right != nullptr) {
            if (this->left->height  > this->right->height)
                this -> height = this->left->height + 1;
            else
                this -> height = this->right->height + 1;
            this->heightDiff = this->right->height - this->left->height;
        }
    }
}





#endif //TREES_AVLNODE_H
