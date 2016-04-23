#include <iostream>
#include <fstream>
#include "occindex.h"

OccIndex::OccBlock::OccBlock(unsigned int pos){
    position = pos;
    next = NULL;
    occurrences = std::map<unsigned char, unsigned int>();
}

OccIndex::OccBlock::OccBlock(unsigned int pos, OccBlock* block){
    position = pos;
    next = NULL;

    occurrences = std::map<unsigned char, unsigned int>(block->occurrences);
}

OccIndex::OccBlock::~OccBlock(){
    occurrences.clear();
}

OccIndex::OccIndex(){
    head = new OccBlock(BLOCKSIZE);
    tail = head;
}

OccIndex::~OccIndex(){
    OccBlock* block = head;
    while (block){
        block = head->next;
        head->occurrences.clear();
        delete head;
        head = block;
    }
}

unsigned int OccIndex::OccBlock::occInBlock(unsigned char c){
    return occurrences[c];
}

void OccIndex::createOccIndex(std::istream& in){
    OccBlock* block = head;
    unsigned int blockSize = 0;

    char c;
    while (in.get(c)){
        if (blockSize >= BLOCKSIZE){
            block->next = new OccBlock(block->position + blockSize, block);
            blockSize = 0;
            block = block->next;
            tail = block;
        }
        block->occurrences[c]++;
        blockSize++;
    } 
}

unsigned int OccIndex::occ(unsigned char c, unsigned int q, std::istream& in){
    OccBlock* block = getIndexBlock(q);

    unsigned int occurrences = 0;
    unsigned int i = 0;

    in.clear();
    if (block){
        in.seekg(block->position, in.beg);
        i = block->position;
        occurrences = block->occInBlock(c);
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

OccIndex::OccBlock* OccIndex::getIndexBlock(unsigned int q){
    OccBlock* block = head;
    while (block->position < q){
        if (block->next){
            if (block->next->position < q){
                block = block->next;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if (block->position < q){
        return block;
    } else {
        return NULL;
    }
}


// Debugging
void OccIndex::OccBlock::print(){
    std::cout << "Block distance: " << position << std::endl;
    std::map<unsigned char, unsigned int>::iterator it;
    for (it = occurrences.begin(); it != occurrences.end(); it++){
        std::cout << "Character: " << it->first << " Occurrences: " << it->second << std::endl;
    }
}

void OccIndex::print(){
    OccBlock* block = head;
    while (block){
        block->print();
        block = block->next;
    }
}
