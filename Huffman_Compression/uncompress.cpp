/* Implementation of Uncompress cpp
 * File: uncompress.cpp
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
	BitInputStream bitIS(inF);
	string val;
	string index;
	int sym;
	int i = 0;
	long size = 0;

	//Open Input File
	inF.open(argv[1], std::ifstream::in | std::ifstream::binary);
	
	if (!inF)
	{
		cout<<"Error: Input file not found!"<<endl;
		return -1;
	}



	//Read bytes for header 
	while (1) {
		if (inF.bad()|| inF.peek()==';') 
		{
			break;
		}
		getline ( inF, index, ',' );
		getline ( inF, val, ' ' );

		//Break with eof is reached
		if(inF.eof()) 
		{
			break;
		}

		symbolCount[atoi(index.c_str())] = atoi(val.c_str());
	}
	getline ( inF, val, ';' );
	getline ( inF, val, ';' );
	size = atoi(val.c_str());


	//Open Output file for writing
	outF.open(argv[2], std::ofstream::out | std::ofstream::binary);

	//Build huffmant tree
	hTree.build(symbolCount);

	//If size>0 then enter this loop, file contains elements
	if(size) {
		// decode to outF
		while (i < size) {
			//Break if input file is bad
			if (inF.bad())
			{
				break;
			}
			sym=(hTree.decode(bitIS));
			outF<<(char)sym;

			//Break if end of input file is reached
			if(inF.eof()) 
			{
				break;
			}

			i++;
		}

		bitIS.fill();
	}


	//Close both input and output files
	inF.close();
	outF.close();

	return 0;
}
