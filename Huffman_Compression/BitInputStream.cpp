/* Implementation of BitInputStream cpp
 * File: BitInpurStream.cpp
 * Name: Adam Li 
 * Account: adl013
 * Name Ahmad Ghayaisi
 * Account: aghayais
 * Programming Assignment 3 Huffman Tree Algorithm: Compress and Uncompress
 * February 25th 2014
 */

#include "BitInputStream.hpp"


int BitInputStream::readBit() {
    //if all bits in buffer are read, fill buffer first
    if(nbits==8) fill();

    //get bit at appropriate location in bit
    //bufer and return appropriate int
    int v = buf & 1<<(7-nbits); 

    nbits++;
    return v;
}

void BitInputStream::fill() {
    //buffer gets filled with what is in the input stream
    buf = in.get();

    //reset nbits buffer index
    nbits=0;
}
