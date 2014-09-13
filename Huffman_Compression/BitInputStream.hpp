/* Implementation of BitInputStream cpp
 * File: BitInputStream.hpp
 * Name: Adam Li 
 * Account: adl013
 * Name Ahmad Ghayaisi
 * Account: aghayais
 * Programming Assignment 3 Huffman Tree Algorithm: Compress and Uncompress
 * February 25th 2014
 */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
#include <bitset>

using namespace std;

/* A class for reading bits (and ints) from an istream
 */

class BitInputStream {
private:
    std::istream& in; //the istream to delegate to
    char buf;   //the buffer of bits
    
    int nbits; //the buffer index
    char *fileName;

public:
    /* Initialize a BitInputStream object, given an istream.
     */
    BitInputStream(istream& s) : in(s), buf(0), nbits(8) { }
    
    /** Read the next bit from the bit buffer
     * if the bit buffer is currently empty
     *  -> fill the bit buffer by reading a char form the istream first
     *  Return the bit read as the least significant bit of an int.
     *  Return -1 if EOF
     *
     *  This must be consistent with BitOutputStream::writeBit(), 
     *  in terms of ordering of bits in the stream.
     */
    int readBit();

    /* fill the buffer if all bits in buffer are read
     */
    void fill();
};

#endif //BITINPUTSTREAM_HPP
