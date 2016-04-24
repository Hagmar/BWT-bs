#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include "ctable.h"
#include "occindex.h"

CTable::CTable(std::istream& ixIn){
    std::memset(table, 0, sizeof(table));

    ixIn.seekg(-BLOCKSIZE, ixIn.end);
    unsigned int previous = 0;
    unsigned int occurrences = 0;
    for (int i = 0; i < 256; i++){
        table[i] = previous;
        ixIn.read((char*) &occurrences, sizeof(unsigned int));
        previous += occurrences;
    }
}

unsigned int CTable::getC(unsigned char c){
    return table[c];
}

// Debugging
void CTable::print(){
    for (int i = 0; i < 256; i++){
        std::cout << "Character: " << table[i] << std::endl;
    }
}
