#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/* Implementatino of the Randomized Search Tree class
 *
 * Authors:
 * Adam Li (adl013)
 * Saurabh Rane (srane)
 */

template <typename Data>
class RST : public BST<Data> {

public:
    //define constructor to srand(
    RST(){
        //Sets a "randomized" seed based on time
        srand(time(NULL));
    }

    int randomPriority() {
        return rand();//Finds random priority
    }

    virtual std::pair<typename BST<Data>::iterator,bool>
        insert(const Data& item) {
            //calls insert to insert the item in BST algorithm way
            std::pair<typename BST<Data>::iterator, 
                bool> node = BST<Data>::insert(item);
            
            //assign it a randomly generated priority
            node.first.curr->info = randomPriority(); 

            //temporary pointer to the current BSTNode
            BSTNode<Data>* temp = node.first.curr; 
           
            if(temp->parent == nullptr){
                return node;
            }
            //bubble up algorithm because current node's priority is higher
            while(temp->parent && temp->parent->info < temp->info) {
                BSTNode<Data>* X = temp->parent; //temp node to hold parent
                //node is parent's left child
                if(X->left == temp) {
                    //Reset child pointers
                    BSTNode<Data> * L = X->left;
                    X->left = L->right;
                    if(L->right)
                        L->right->parent = X;
                    L->right = X;
                    //Node is in right subtree
                    if(X->parent && X->parent->right == X) {
                        //Reset parent pointers
                        X->parent->right = L;
                        L->parent = X->parent;
                        X->parent = L;
                    }
                    //Node is in left subtree
                    else{
                        //Reset parent pointers
                        if(X->parent)
                            X->parent->left = L;
                        L->parent = X->parent;
                        X->parent = L;
                    }
                    temp = L;
                }

                //node is parent's right child
                else {
                    BSTNode<Data> * R = X->right;
                    X->right = R->left;
                    if(R->left)
                        R->left->parent = X;
                    R->left = X;
                    //parent is parent's left child
                    if(X->parent && X->parent->left == X) {
                        X->parent->left = R;
                        R->parent = X->parent;
                        X->parent = R;
                    }
                    //parent is parent's right child
                    else {
                        if(X->parent)
                            X->parent->right = R;
                        R->parent = X->parent;
                        X->parent = R;
                    }
                    temp = R;
                }
            }
            //check parent's null
            if(!temp->parent)
                BST<Data>::root = temp;
            return node;
        }
};
#endif //RST_HPP
