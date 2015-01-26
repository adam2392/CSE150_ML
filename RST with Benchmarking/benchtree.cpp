//1. take in string "bst" rst or set and indicate whether benchmarkeing
//should be done using those
//2.a string which must be sorted or shuffled and indicate 
//whehter keys inserted in structure are inserted in sorted order or 
//randomized orde
//
//3.int which specifies max size of tree to be built in the bench
//
//4.int that specifies how many runs will be done and averaged
//over for each N
//
//N should be powers of 2 minus 1
/* Adam Li (adl013)
 * Saurabh Rane (srane)
 */

#include "countint.hpp"
#include "RST.hpp"
#include <cmath>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

/*
 * Benchmarking of the performance of a RST Implementation, ordinary BST
 * implementation and the C++ STL std::set structure.
 * Performance means how many comparisons were required to do a successful
 * find operation
 *
 * Hold instances of the countint class 
 */

int main(int argc, char** argv) {
    //read in the commands
    int maxnum = atoi(argv[3]);
    int runs = atoi(argv[4]);
    int N = 1;
    int Nbuffer = 2;

    if(argc != 5)
    {
        cout<<"not correct # of arguments\n";
        return -1;
    }
    //print out of comments section
    cout<<"# Benchmarking average number of comparisons for successful find"
        <<"\n# Data Structure: "<<argv[1]<<"\n# Data: "<<argv[2]
        <<"\n# N is powers of 2, minus 1, from 1 to "<<maxnum
        <<"\n# Averaging over "<<runs<<" runs for each N"<<"\n#\n"
        <<"# N\tavgcomps\tstdev\n";
    
    double avgcomps[runs];
    double sumcomps = 0;
    double squaresum = 0;
    double stdev = 0;

    //set up bst/rst/set command
    BST<countint>* b = new BST<countint>();
    BST<countint>* r = new RST<countint>();
    std::set<countint>* s = new std::set<countint>();

    //number of runs to do
    while(N < maxnum) {
        for(int j=0; j<runs; j++) {
            
            //create STL vector of countints
            std::vector<countint> v;
            v.clear();
            for(int i=0; i<N; i++) {
                v.push_back(i);
            }

            if(strcmp(argv[2], "shuffled")==0) {
                //create STL vector of countints, in shuffled order
                std::random_shuffle(v.begin(), v.end());
            }
            //sort the vector v
            else if (strcmp(argv[2], "sorted")==0) {}
            else {
                cout<<"Insert correct command for sorted/shuffled!\n";
                return -1;
            }
            std::vector<countint>::iterator vit = v.begin();
            std::vector<countint>::iterator ven = v.end();

            //determine structures insert
            //first check bst
            b->clear();
            r->clear();
            s->clear();
            if (strcmp(argv[1], "bst")==0) {
                for(; vit!=ven; ++vit) {
                    b->insert(*vit);
                }
            }
            //check rst
            else if (strcmp(argv[1], "rst")==0) {
                for(; vit!=ven; ++vit) {
                    r->insert(*vit);
                }
            }
            //check set
            else if (strcmp(argv[1], "set")==0)  {
                for(; vit!=ven; ++vit) {
                    s->insert(*vit);
                }
            }
            //incorrect command
            else {
                cout<<"Insert correct command for bst/rst/set!\n";
                return -1;
            }
            
            //clear comparison counter
            countint::clearcount();
            //find keys in structure
            for(vit = v.begin(); vit!=ven; ++vit) {
                if(strcmp(argv[1], "bst") == 0) {
                    b->find(*vit);
                }
                else if(strcmp(argv[1], "rst") == 0) {
                    r->find(*vit);
                }
                else { 
                    s->find(*vit);
                }
            }
            //average count
            avgcomps[j] = countint::getcount() / (double) N;
          }
        //calculate the sum of counts and the squared sum of counts
        for(int j=0;j<runs;j++) {
            sumcomps = sumcomps + avgcomps[j];
            squaresum = squaresum + avgcomps[j]*avgcomps[j];
        }
        //average the sum and squared sum
        sumcomps = sumcomps/runs;
        squaresum = squaresum/runs;

        //calculate the stdev per N based on the runs
        double inter = squaresum - sumcomps* sumcomps;
        if(inter < 0)
            inter = inter * -1;

        stdev = sqrt(inter);
        
        //print out the table
        cout<<N<<"\t"<<sumcomps<<"\t\t"<<stdev<<"\n";
        sumcomps = 0;
        squaresum = 0;

        //recalculate N
        Nbuffer = Nbuffer*2;
        N = Nbuffer-1;  
    }
    return 1;
}

