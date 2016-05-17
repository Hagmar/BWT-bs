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
    // If ixIn.good() is true, then the index file already exists. Otherwise,
    // it needs to be created
    if (!ixIn.good()){
        ixIn.close();
        blocksWritten = createOccIndex(in);
        ixIn.open(indexFile, std::ifstream::binary);
    } else {
        // Determine how many occurrence blocks exist in the index file
        ixIn.seekg(0, ixIn.end);
        blocksWritten = ixIn.tellg() / (BLOCKSIZE);
    }

    generateCTable(blocksWritten, ixIn, in);
}

// Set up the charMap for looking up character indices
void Index::initializeCharMap(){
    // Tab, newline and carriage return
    charMap[9] = 0;
    charMap[10] = 1;
    charMap[13] = 2;
    // Other visible ASCII characters
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

// Performs a C-table lookup for character c
unsigned int Index::getC(unsigned char c){
    return cTable[ charMap[c] ];
}

// Scans the input file and generates an index file for it
unsigned int Index::createOccIndex(std::istream& in){
    unsigned int indexArray[BLOCKELEMENTS] = {0};
    unsigned int blocksWritten = 0;
    std::ofstream out(indexFile, std::ofstream::trunc | std::ofstream::binary);

    unsigned char charIndex;
    char fileBuffer[BLOCKSIZE];
    while (true){
        in.read(fileBuffer, BLOCKSIZE);
        if (in.gcount() == BLOCKSIZE){
            for (int i = 0; i < BLOCKSIZE; i++){
                charIndex = charMap[fileBuffer[i]];
                indexArray[charIndex]++;
            }
            // Once enough characters have been read, write the block to the index
            writeBlockToIndex(indexArray, out);
            blocksWritten++;
        } else {
            break;
        }
    } 
    in.clear();
    out.close();
    return blocksWritten;
}

// Append an occurrence block to the index file
void Index::writeBlockToIndex(unsigned int indexArray[BLOCKELEMENTS], std::ofstream& out){
    out.write((char*) indexArray, BLOCKSIZE);
}

// Create the C-table using the index and input file
void Index::generateCTable(unsigned int blocksWritten, std::istream& ixIn,
        std::istream& in){
    std::memset(cTable, 0, sizeof(cTable));

    // Start by getting the character occurrences from the index file
    unsigned int occurrences = 0;
    if (blocksWritten){
        ixIn.seekg((blocksWritten - 1) * BLOCKSIZE, ixIn.beg);
        ixIn.read((char*) cTable + sizeof(unsigned int),
                BLOCKSIZE - sizeof(unsigned int));
    }

    // Skip all the characters already counted by the index
    in.seekg(blocksWritten * BLOCKSIZE, in.beg);

    // Count all the remaining characters
    char c;
    while (in.get(c)){
        cTable[ charMap[c] + 1]++;
    }

    // Make each entry in the table the sum of all previous entries
    for (int i = 1; i <= BLOCKELEMENTS; i++){
        cTable[i] += cTable[i-1];
    }
}

// Count the number of occurrences of character c up until, but not including,
// index q
unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in, std::istream& ixIn){
    unsigned int blockOffset = q / BLOCKSIZE;

    unsigned char charIndex = charMap[c];
    unsigned int occurrences = 0;
    unsigned int i = 0;

    // Read the number of c's which have occurred up until the index closest to
    // q which can be found in the index file
    if (blockOffset){
        ixIn.seekg((blockOffset-1) * BLOCKSIZE + (charIndex * sizeof(unsigned int)), ixIn.beg);
        ixIn.read((char*) &occurrences, sizeof(unsigned int));
        in.seekg(blockOffset * BLOCKSIZE, in.beg);
        i = blockOffset * BLOCKSIZE;
    } else {
        in.seekg(0, in.beg);
    }

    // Count the remaining occurrences of c from the end of the occurrence
    // block until q
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
