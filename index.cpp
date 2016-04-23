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
    std::cout << "Occerence index complete" << std::endl;
    cTable = new CTable(occIndex);
    std::cout << "C-table complete" << std::endl;
    recordIndex = new RecordIndex();
    recordIndex->createIndex(occIndex, cTable, in);
    std::cout << "Record index complete" << std::endl;
}

unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in){
    return occIndex->occ(c, q, in);
}

unsigned int Index::getC(unsigned char c, bool includeC){
    return cTable->getC(c, includeC);
}

// Debugging
void Index::printAll(){
    occIndex->print();
    std::cout << std::endl;
    cTable->print();
    std::cout << std::endl;
    recordIndex->print();
}
