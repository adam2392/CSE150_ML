/* Implementation of BitInputStream cpp
 * File: BitOutputStream.cpp
 * Name: Adam Li 
 * Account: adl013
 * Name Ahmad Ghayaisi
 * Account: aghayais
 * Programming Assignment 3 Huffman Tree Algorithm: Compress and Uncompress
 * February 25th 2014
 */
#include "BitOutputStream.hpp"

/* Implementation of BitOutputStream cpp
 *
 * @author Adam Li 2014
 */

void BitOutputStream::writeBit(int bit) {
    //is bit buffer full? -> flush it
    if(nbits==8) flush();

    //write least significant bit of 'bit' into buffer
    //at current index
    buf = buf | bit<<(7-nbits);
    
    //increment the index
    nbits++;
}

void BitOutputStream::flush() {
    //put into output stream what is in buffer
    out.put(buf);

    //flush out the output stream
    out.flush();

    //reset buffer and nbits index
    buf=nbits=0;
}

