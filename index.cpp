#include <fstream>
#include <iostream>
#include <cstring>
#include "index.h"

Index::Index(const char* filename, const char* indexFileName){
    indexFile = indexFileName;
    std::ifstream in(filename);

    createOccIndex(in);
    std::cout << "Occerence index complete" << std::endl;

    std::ifstream ixIn(indexFile);

    generateCTable(ixIn);
    std::cout << "C-table complete" << std::endl;
}

unsigned int Index::getC(unsigned char c){
    return cTable[c];
}

void Index::createOccIndex(std::istream& in){
    unsigned int indexArray[128] = {0};
    unsigned int blockSize = 0;
    std::ofstream out(indexFile, std::ofstream::trunc | std::ofstream::binary);

    char c;
    while (in.get(c)){
        indexArray[(unsigned char) c]++;
        if (blockSize >= BLOCKSIZE){
            writeBlockToIndex(indexArray, out);
            blockSize = 0;
        }
        blockSize++;
    } 
    // TODO
    // What happens when block isn't complete?
    writeBlockToIndex(indexArray, out);
    out.close();
}

void Index::writeBlockToIndex(unsigned int indexArray[128], std::ofstream& out){
    out.write((char*) indexArray, 128 * sizeof(unsigned int));
}

void Index::generateCTable(std::istream& ixIn){
    std::memset(cTable, 0, sizeof(cTable));

    ixIn.seekg(-BLOCKSIZE, ixIn.end);
    unsigned int previous = 0;
    unsigned int occurrences = 0;
    for (int i = 0; i < 128; i++){
        cTable[i] = previous;
        ixIn.read((char*) &occurrences, sizeof(unsigned int));
        previous += occurrences;
    }
}

unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in, std::istream& ixIn){
    unsigned int blockOffset = q / BLOCKSIZE;

    unsigned int occurrences = 0;
    unsigned int i = 0;

    if (blockOffset){
        ixIn.seekg((blockOffset-1) * BLOCKSIZE + (c * sizeof(unsigned int)));
        ixIn.read((char*) &occurrences, sizeof(unsigned int));
        i = blockOffset * BLOCKSIZE;
        in.seekg(i);
    } else {
        in.seekg(0);
    }

    char readChar;
    for (; i <= q; i++){
        if (!in.get(readChar)){
            break;
        }
        if (c == readChar){
            occurrences++;
        }
    }
    return occurrences;
}

// Debugging
void Index::print(){
    std::cout << std::endl;
    for (int i = 0; i < 128; i++){
        std::cout << "Character: " << cTable[i] << std::endl;
    }
}
