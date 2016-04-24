#include <fstream>
#include <iostream>
#include "index.h"
#include "occindex.h"
#include "ctable.h"

Index::Index(const char* filename, const char* indexFileName){
    indexFile = indexFileName;
    std::ifstream in(filename);

    occIndex = new OccIndex();
    occIndex->createOccIndex(in, indexFile);
    std::cout << "Occerence index complete" << std::endl;

    std::ifstream ixIn(indexFile);

    cTable = new CTable(ixIn);
    std::cout << "C-table complete" << std::endl;
}

unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in, std::istream& ixIn){
    return occIndex->occ(c, q, in, ixIn);
}

unsigned int Index::getC(unsigned char c){
    return cTable->getC(c);
}

// Debugging
void Index::printAll(){
    occIndex->print();
    std::cout << std::endl;
    cTable->print();
}
