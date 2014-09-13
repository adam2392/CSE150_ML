/* Implementation of HCTree cpp
 * File: HCTree.cpp
 * Name: Adam Li 
 * Account: adl013
 * Name Ahmad Ghayaisi
 * Account: aghayais
 * Programming Assignment 3 Huffman Tree Algorithm: Compress and Uncompress
 * February 25th 2014
 */

#include "HCTree.hpp"
#include "HCNode.hpp"
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <fstream>

/* Implementation of the HCTree class
 * See: HCTree.hpp
 * @author Adam Li 
 * Ahmad Ghayaisi
 * (c) 2014
 */

/* Use huffman alg to build huffman coding trie
 * precondition: freqs is vector of ints
 * freqs[i] is frequency of occurence of byte i in message
 * Postcondidtion: root points to root of trie,
 * and leaves[i] points to leaf node containing byte i.
 */

void HCTree::build(const vector<int>& freqs){

	//build forest of single node trees
	//each node in forest gets symbol from set w/ freqs 
	//creates a priority queue called pointQ 
	//of HCNode * types, in a vector
	//that gets passed a HCNodePtrComparator

	std::priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
	HCNode* hnOne;  //First pointer for pq
	HCNode* hnTwo; //Second pointer for pq
	HCNode* temp;   //Temporary pointer for pq

	//Build nodes for all the symbols in the file
	for(unsigned int i=0; i < freqs.size(); i++){
		if(freqs[i] !=0){
			leaves[i] = new HCNode(freqs[i], (byte)i, 0, 0, 0);
			pq.push(leaves[i]);
		}
	}

	//Case file is empty
	if(pq.size() == 0)
	{ 
		return;            
	}

	//Case if only one symbol exists	
	if(pq.size() == 1){ 
		root= new HCNode(pq.top()->count, pq.top()->symbol, pq.top(), 0, 0);
		pq.top()->p = root;
		pq.pop();
		return;
	}

	// Find the two lowest nodes then makes tree and inserts til done.
	while(pq.size()>1)
	{
		hnOne = pq.top();
		pq.pop();
		hnTwo = pq.top();
		pq.pop();

        //create a temporary HCNode
		temp = new HCNode( (hnOne->count + hnTwo->count), hnOne->symbol, 
				hnOne, hnTwo, 0);
		hnOne->p = temp;
		hnTwo->p = temp;
		pq.push(temp);
	}

	//Root is set to last node
	root = pq.top();                   
	pq.pop();
}                                          



/* Write to given bitoutputstream
 * the sequence of bits coded in given symbol.
 * precondition: build() has been called to create the tree,
 * and initializes root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
	//Store bits going from leaf to node
	std::stack<int> stream;

	//Node pointer to symbol at bottom of tree
	HCNode* nodeSymbol = leaves[(int)symbol];  

	//While not zero, because when zero, we have reached the root
	while(nodeSymbol->p != 0)
	{
		if(nodeSymbol->p->c0 == nodeSymbol)
		{
			stream.push(0);
		}
		else
		{
			stream.push(1);
		}

		nodeSymbol = nodeSymbol->p;
	}

	//Empty stack so output file is put in correct order
	while(!stream.empty())
	{          
		out.writeBit(stream.top());
		stream.pop();
	}
}                       

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const {
	HCNode* traversal = root; //traversal node to traverse tree
	int byte;   //initialize byte for reading

	//Empty stack into the output file
	while(1){                             
		byte = in.readBit();
		if(byte == -1) 
		{
			break;
		}

		// Traverse Left
		if(byte == 0) {
			traversal = traversal->c0;

			// No children case
			if (!(traversal->c0) && !(traversal->c1)) {
				return ((int)traversal->symbol);
			}
		}
		else {
			traversal = traversal->c1;

			// No children case
			if (!(traversal->c0) && !(traversal->c1)) {
				return ((int)traversal->symbol);
			}
		}
	}
	return 1;
}                                       


/**
  *Helper method for the destructor
  */
void deleteAllNodes (HCNode* node) {
	if(!node) 
	{
		return;
	}
	deleteAllNodes(node->c0);
	deleteAllNodes(node->c1);

	delete node;
	return;
}

/**
 * Destructor method
 */
HCTree::~HCTree() {
	deleteAllNodes(root);
}




