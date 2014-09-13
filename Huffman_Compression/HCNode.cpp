/* Implementation of HCNode cpp
 * File: HCNode.cpp
 * Name: Adam Li 
 * Account: adl013
 * Name Ahmad Ghayaisi
 * Account: aghayais
 * Programming Assignment 3 Huffman Tree Algorithm: Compress and Uncompress
 * February 25th 2014
 */

#include "HCNode.hpp"
//overload operator <
bool HCNode::operator<(const HCNode& other) {
  
	return this -> count > other.count;
 
}

//compare two HCNode's using < operator
bool HCNode::comp(HCNode* one, HCNode* other) {
    return (*one)<(*other);
}
