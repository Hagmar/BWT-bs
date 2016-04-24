#include <fstream>
#include <iostream>
#include <cstring>
#include "index.h"
#include "occindex.h"

Index::Index(const char* filename, const char* indexFileName){
    indexFile = indexFileName;
    std::ifstream in(filename);

    occIndex = new OccIndex();
    occIndex->createOccIndex(in, indexFile);
    std::cout << "Occerence index complete" << std::endl;

    std::ifstream ixIn(indexFile);

    generateCTable(ixIn);
    std::cout << "C-table complete" << std::endl;
}

unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in, std::istream& ixIn){
    return occIndex->occ(c, q, in, ixIn);
}

unsigned int Index::getC(unsigned char c){
    return cTable[c];
}

void Index::generateCTable(std::istream& ixIn){
    std::memset(cTable, 0, sizeof(cTable));

    ixIn.seekg(-BLOCKSIZE, ixIn.end);
    unsigned int previous = 0;
    unsigned int occurrences = 0;
    for (int i = 0; i < 256; i++){
        cTable[i] = previous;
        ixIn.read((char*) &occurrences, sizeof(unsigned int));
        previous += occurrences;
    }
}

// Debugging
void Index::print(){
    occIndex->print();
    std::cout << std::endl;
    for (int i = 0; i < 256; i++){
        std::cout << "Character: " << cTable[i] << std::endl;
    }
}
