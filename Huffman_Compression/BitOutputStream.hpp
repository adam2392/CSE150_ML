/* Implementation of BitInputStream cpp
 * File: BitOutputStream.hpp
 * Name: Adam Li 
 * Account: adl013
 * Name Ahmad Ghayaisi
 * Account: aghayais
 * Programming Assignment 3 Huffman Tree Algorithm: Compress and Uncompress
 * February 25th 2014
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <bitset>

using namespace std;

/* A class for writing bits (and chars and ints) to an ostream
 */

class BitOutputStream {

private:
    std::ostream & out; //outputstream to delegate to
    char buf;      //buffer of bits
    int nbits;       //bit buffer index

public:
    BitOutputStream(std::ostream& s) : out(s), buf(0), nbits(0) { }
    
    /* Write the least significant bit of the argument into
     * the bit buffer, and increment the bit buffer index.
     *
     * put writes bytes
     *
     * Flush to the ostream first if the bit buffer is full.
     * This must be consistent with BitInputStream::readBit()
     */
    void writeBit(int bit);

    /* If the bit buffer contains any bits, flush bit bufer to ostream.
     * clear bit buffer and set bit buffer index to 0.
     * Also flush ostream.
     */
    void flush();
};

#endif //BITOUTPUTSTREAM_HPP

