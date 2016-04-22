#include <fstream>
#include <iostream>
#include "index.h"
#include "occindex.h"
#include "ctable.h"
#include "recordindex.h"

Index::Index(const char* filename){
    std::ifstream in(filename);

    occIndex = new OccIndex();
    occIndex->createOccIndex(in);
    cTable = new CTable(occIndex);
    recordIndex = new RecordIndex();
}

unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in){
    return occIndex->occ(c, q, in);
}

unsigned int Index::getC(unsigned char c){
    return cTable->getC(c);
}

// Debugging
void Index::printAll(){
    occIndex->print();
    std::cout << std::endl;
    cTable->print();
    std::cout << std::endl;
    recordIndex->print();
}
