#include <iostream>
#include <fstream>
#include "occindex.h"

OccIndex::OccIndex(){
    index = std::map<unsigned int, std::map<unsigned char, unsigned int> >();
    index[BLOCKSIZE] = std::map<unsigned char, unsigned int>();
}

OccIndex::~OccIndex(){
    std::map<unsigned int, std::map<unsigned char, unsigned int> >::
        iterator it;
    for (it = index.begin(); it != index.end(); it++){
        it->second.clear();
    }
    index.clear();
}

void OccIndex::createOccIndex(std::istream& in){
    unsigned int blockSize = 0;

    unsigned int blockPos = BLOCKSIZE;
    std::map<unsigned char, unsigned int>* block = &index[BLOCKSIZE];
    char c;
    while (in.get(c)){
        if (blockSize >= BLOCKSIZE){
            blockPos += BLOCKSIZE;
            index[blockPos] = std::map<unsigned char, unsigned int>(*block);
            block = &index[blockPos];
            blockSize = 0;
        }
        (*block)[c]++;
        blockSize++;
    } 
}

unsigned int OccIndex::occ(unsigned char c, unsigned int q, std::istream& in){
    unsigned int blockPos = q - (q % BLOCKSIZE);

    unsigned int occurrences = 0;
    unsigned int i = 0;

    in.clear();
    if (blockPos){
        in.seekg(blockPos, in.beg);
        i = blockPos;
        occurrences = index[blockPos][c];
    } else {
        in.seekg(0, in.beg);
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
    std::map<unsigned int, std::map<unsigned char, unsigned int> >::iterator it;
    std::map<unsigned char, unsigned int>::iterator blockIt;
    for (it = index.begin(); it != index.end(); it++){
        std::cout << "Block distance: " << it->first << std::endl;
        for (blockIt = it->second.begin(); blockIt != it->second.end(); blockIt++){
            std::cout << "Character: " << blockIt->first << " Occurrences: " << blockIt->second << std::endl;
        }
    }
}
