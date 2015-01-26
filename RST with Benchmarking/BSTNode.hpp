/*********************************************************************
 

					Adam Li and Saurabh Rane
					CSE 100, Winter 2014
					Due: Monday Feb. 4th, 2014
					

			Assignment 02

file name: BSTNode.hpp
Description: Contains functions and methods used in the Node layer
of BST.
*********************************************************************/
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 */


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ // TODO
  BSTNode<Data>* successor() const {
      const BSTNode<Data>* current = this; //current node
      BSTNode <Data>* next;
      //current node is null; tree is empty
      if(current == NULL){
          return nullptr;
      }
      //node has right child and no left child
      if(current->right){
          next = current->right;
          while(next->left){ 
              //Find leftmost child in right branch
              next = next->left;
          }
          return next;
      }
      else if(current->parent){
        next = current->parent;
        //node has no right child and is right child of parent       
        if(!current->right && current->parent->right == current){
            while(next->parent){
                //Keep moving up the tree
                if(next->parent->right == next)
                    //if parent is right child keep moving up
                    next = next->parent;
                else if(next->parent->left == next){
                    //if parent is left child, parent is successor
                    next = next->parent;
                    return next;
                }
            }
            if(!next->parent)//Case of root
                return nullptr;
            return next;
        }
        //node has no right child and is left child of parent
        else if(!current->right && current->parent->left == current){
            return current->parent;
        }
      }
      //node has no parent
      else if(!current->parent)
          return nullptr;
      return nullptr;
  }

}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP

