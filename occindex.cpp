#include <iostream>
#include <fstream>
#include "occindex.h"

void OccIndex::createOccIndex(std::istream& in, const char* indexFile){
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
    writeBlockToIndex(indexArray, out);
}

void OccIndex::writeBlockToIndex(unsigned int indexArray[128], std::ofstream& out){
    out.write((char*) indexArray, 128*sizeof(unsigned int));
}

unsigned int OccIndex::occ(unsigned char c, unsigned int q, std::istream& in, std::istream& ixIn){
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
void OccIndex::print(){
    //std::map<unsigned int, std::map<unsigned char, unsigned int> >::iterator it;
    //std::map<unsigned char, unsigned int>::iterator blockIt;
    //for (it = index.begin(); it != index.end(); it++){
        //std::cout << "Block distance: " << it->first << std::endl;
        //for (blockIt = it->second.begin(); blockIt != it->second.end(); blockIt++){
            //std::cout << "Character: " << blockIt->first << " Occurrences: " << blockIt->second << std::endl;
        //}
    //}
}
