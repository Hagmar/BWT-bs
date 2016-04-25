#include <fstream>
#include <iostream>
#include <cstring>
#include "index.h"

Index::Index(const char* filename, const char* indexFileName){
    indexFile = indexFileName;
    std::ifstream in(filename);

    unsigned int blocksWritten = createOccIndex(in);

    std::ifstream ixIn(indexFile);

    generateCTable(blocksWritten, ixIn, in);
}

unsigned int Index::getC(unsigned char c){
    return cTable[c];
}

unsigned int Index::createOccIndex(std::istream& in){
    unsigned int indexArray[128] = {0};
    unsigned int blockSize = 0;
    unsigned int blocksWritten = 0;
    std::ofstream out(indexFile, std::ofstream::trunc | std::ofstream::binary);

    char c;
    while (in.get(c)){
        indexArray[(unsigned char) c]++;
        if (blockSize >= BLOCKSIZE){
            writeBlockToIndex(indexArray, out);
            blockSize = 0;
            blocksWritten++;
        }
        blockSize++;
    } 
    in.clear();
    out.close();
    return blocksWritten;
}

void Index::writeBlockToIndex(unsigned int indexArray[128], std::ofstream& out){
    out.write((char*) indexArray, 128 * sizeof(unsigned int));
}

void Index::generateCTable(unsigned int blocksWritten, std::istream& ixIn,
        std::istream& in){
    std::memset(cTable, 0, sizeof(cTable));

    unsigned int occurrences = 0;
    if (blocksWritten){
        ixIn.seekg(-BLOCKSIZE, ixIn.end);
        for (int i = 0; i < 128 - 1; i++){
            ixIn.read((char*) &occurrences, sizeof(unsigned int));
            cTable[i+1] = occurrences;
        }
    }

    in.seekg(blocksWritten * BLOCKSIZE, in.beg);
    char c;
    while (in.get(c)){
        cTable[((unsigned char) c)+1]++;
    }

    for (int i = 1; i < 128; i++){
        cTable[i] += cTable[i-1];
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
