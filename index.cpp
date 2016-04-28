#include <fstream>
#include <iostream>
#include <cstring>
#include "index.h"

Index::Index(const char* filename, const char* indexFileName){
    indexFile = indexFileName;
    std::ifstream in(filename);
    std::ifstream ixIn(indexFile, std::ifstream::binary);

    initializeCharMap();

    unsigned int blocksWritten;
    if (!ixIn.good()){
        ixIn.close();
        blocksWritten = createOccIndex(in);
        ixIn.open(indexFile, std::ifstream::binary);
    } else {
        ixIn.seekg(0, ixIn.end);
        blocksWritten = ixIn.tellg() / (BLOCKSIZE);
    }

    generateCTable(blocksWritten, ixIn, in);
}

void Index::initializeCharMap(){
    // Tab, newline and carriage return
    charMap[9] = 0;
    charMap[10] = 1;
    charMap[13] = 2;
    for (unsigned char i = 3; i <= BLOCKELEMENTS; i++){
        charMap[i+29] = i;
    }

    // Dummy entries to make lookup of C[c+1] possible
    charMap[11] = 2;
    charMap[12] = 2;
    for (unsigned char i = 14; i < 32; i++){
        charMap[i] = 3;
    }
}

unsigned int Index::getC(unsigned char c){
    return cTable[ charMap[c] ];
}

unsigned int Index::createOccIndex(std::istream& in){
    unsigned int indexArray[BLOCKELEMENTS] = {0};
    unsigned int blockSize = 0;
    unsigned int blocksWritten = 0;
    std::ofstream out(indexFile, std::ofstream::trunc | std::ofstream::binary);

    char c;
    unsigned char charIndex;
    while (in.get(c)){
        charIndex = charMap[c];
        indexArray[charIndex]++;
        blockSize++;
        if (blockSize >= BLOCKCAPACITY){
            writeBlockToIndex(indexArray, out);
            blockSize = 0;
            blocksWritten++;
        }
    } 
    in.clear();
    out.close();
    return blocksWritten;
}

void Index::writeBlockToIndex(unsigned int indexArray[BLOCKELEMENTS], std::ofstream& out){
    out.write((char*) indexArray, BLOCKSIZE);
}

void Index::generateCTable(unsigned int blocksWritten, std::istream& ixIn,
        std::istream& in){
    std::memset(cTable, 0, sizeof(cTable));

    unsigned int occurrences = 0;
    if (blocksWritten){
        ixIn.seekg((blocksWritten - 1) * BLOCKSIZE, ixIn.beg);
        ixIn.read((char*) cTable + sizeof(unsigned int),
                BLOCKSIZE - sizeof(unsigned int));
    }

    in.seekg(blocksWritten * BLOCKSIZE, in.beg);
    char c;
    while (in.get(c)){
        cTable[ charMap[c] + 1]++;
    }

    for (int i = 1; i <= BLOCKELEMENTS; i++){
        cTable[i] += cTable[i-1];
    }
}

unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in, std::istream& ixIn){
    unsigned int blockOffset = q / BLOCKCAPACITY;

    unsigned char charIndex = charMap[c];
    unsigned int occurrences = 0;
    unsigned int i = 0;

    if (blockOffset){
        ixIn.seekg((blockOffset-1) * BLOCKSIZE + (charIndex * sizeof(unsigned int)), ixIn.beg);
        ixIn.read((char*) &occurrences, sizeof(unsigned int));
        in.seekg(blockOffset * BLOCKCAPACITY, in.beg);
        i = blockOffset * BLOCKCAPACITY;
    } else {
        in.seekg(0, in.beg);
    }

    char readChar;
    for (; i < q; i++){
        if (!in.get(readChar)){
            break;
        }
        if (c == readChar){
            occurrences++;
        }
    }
    return occurrences;
}
