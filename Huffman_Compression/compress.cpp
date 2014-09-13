/* Implementation of Compress cpp
 * File: compress.cpp
 * Name: Adam Li 
 * Account: adl013
 * Name Ahmad Ghayaisi
 * Account: aghayais
 * Programming Assignment 3 Huffman Tree Algorithm: Compress and Uncompress
 * February 25th 2014
 */

#include "HCTree.hpp"
#include <stdlib.h>

using namespace std;

int main(int argc,char **argv) {


	ofstream outF; //Output file
	HCTree hTree;  //Huffman Tree
	ifstream inF;  //Input file
	std::vector<int> symbolCount(256,0);
	BitOutputStream bitOS(outF);
	byte symVec; //Vector to hold symbol


	// Open Inputfile
	inF.open(argv[1], std::ifstream::in | std::ifstream::binary);

	if (!inF)
	{
		cout<<"Error: Input file not found!"<<endl;
		return -1;
	}

	// read byte by byte
	while (1) {

		if (inF.bad())
		{
			break;
		}

		symVec = inF.get();

		if(inF.eof()) 
		{
			break;
		}
		if(symVec < 256 && symVec >= 0)
		{
			symbolCount[symVec]++;
		}

	}

	//Clear Input file
	inF.clear();
	inF.seekg(0, inF.beg);

	// Open Output file
	outF.open(argv[2], std::ofstream::out | std::ofstream::binary);

	//Long to hold size
	long size = 0;

	// write the header to the outF
	for(unsigned int i=0; i < symbolCount.size(); i++)
	{
		size += symbolCount[i];
		if(symbolCount[i] != 0) {
			outF<<i<<','<<symbolCount[i]<<' ';
		}
	}

	outF<<';'<<size<<';';

	//Build HCtree with size of symbol count
	hTree.build(symbolCount);

	// encode to file using out BitOutputStream
	while (1) {
		if (inF.bad())
			break;
		symVec = inF.get();
		if(inF.eof()) 
			break;
		hTree.encode(symVec, bitOS);
	}

	//Flush BitStream
	bitOS.flush();

	// Close input and Output files
	inF.close();
	outF.close();

	return 0;
}
