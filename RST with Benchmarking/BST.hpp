#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair
using namespace std;


/** //TODO: 
 *
 * list real name(s) and login name(s) 
 * Authors:
 * Adam Li (adl013)
 * Saurabh Rane (srane)
 * */

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
      clear(); 
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // TODO
  virtual std::pair<iterator,bool> insert(const Data& item) {
    //Inserting the root Node
    
    if(root == nullptr){//Inserts Root into the tree
		root = new BSTNode<Data>(item);  
        isize++; //increments size 
        return std::make_pair(BST<Data>::iterator(root),true);
	}
    Data check = root->data;
    BSTNode<Data>* curparent = root;
    //Loop that keeps going through tree
    while(1){
        //Checks if item is greater than current data
        if(check < item){
            //Checks to see if there is a node to the right
            if(curparent->right){
                check = curparent->right->data;
                curparent = curparent->right;
            }
            //Inserts node to right if current node has no right child
            else{
                curparent->right = new BSTNode<Data>(item);
                curparent->right->parent = curparent;
                isize++;
                return std::make_pair(BST<Data>::iterator(curparent->right),true); 
            }
        }
        //Checks if item is less tahn current data
        else if(item < check){
            //Checks to see if there is a node to the left
            if(curparent->left){
                check = curparent->left->data;
                curparent = curparent->left;
            }
            //Inserts node to left if current node has no right child
            else{
                curparent->left = new BSTNode<Data>(item);
                curparent->left->parent = curparent;                
                isize++;
                return std::make_pair(BST<Data>::iterator(curparent->left),true); 
            }
        }
        //Final check of duplicate Item
        else 
            return std::make_pair(BST<Data>::iterator(curparent),false);             
    }
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ // TODO
  iterator find(const Data& item) const {
    if(!(root < nullptr) && !(nullptr < root))
        return end();

    Data check = root->data;
    BSTNode<Data>* current = root;


    //Loop that keeps going through tree
    while(1){
        if(!(current < nullptr) && !(nullptr < current))
            return end();


        //Checks if item is greater than current data
        if(check < item){
            //Checks to see if there is a node to the right
            if(current->right){
                check = current->right->data;
                current = current->right;
            }
            //Inserts node to right if current node has no right child
            else
                return end(); 
        }
        //Checks if item is less tahn current data
        else if(item < check){
            //Checks to see if there is a node to the left
            if(current->left){
                check = current->left->data;
                current = current->left;
            }
            //Inserts node to left if current node has no right child
            else
                return end(); 
        }
        //Final check of duplicate Item
        else if(!(check<item) && !(item<check))
            return BST<Data>::iterator(current);             
    } 

 
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
      return isize;

  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ // TODO
  void clear() {
      if(root)
        clearAllNodes(root);
      root = nullptr;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
      if(root==nullptr)
          return false;
      return true;

  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const {
      BSTNode<Data>* current = root;
      //loop to find left most value
      while(current->left)
          current = current->left;
      //return iterator pointing to first item
      return BST<Data>::iterator(current);

  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  private:
    void clearAllNodes(BSTNode<Data>* currentnode) {
      if(currentnode->right)
          clearAllNodes(currentnode->right);
      if(currentnode->left)
          clearAllNodes(currentnode->left);
      delete currentnode;
  }
  

 };


#endif //BST_HPP
