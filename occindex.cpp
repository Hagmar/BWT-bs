#include <iostream>
#include <fstream>
#include "occindex.h"

OccIndex::OccBlock::OccEntry::OccEntry(unsigned char character){
    c = character;
    occ = 0;
    next = NULL;
}

OccIndex::OccBlock::OccBlock(unsigned int pos){
    position = pos;
    head = NULL;
}

OccIndex::OccIndex(){
    head = new OccBlock(0);
    tail = head;
}

void OccIndex::createOccIndex(const char* filename){
    std::ifstream in(filename);
    OccIndex* occurences = new OccIndex();
    OccBlock* block = occurences->head;
    OccBlock::OccEntry* currEntry = NULL;
    unsigned int blockSize = 0;

    char c;
    while (in.get(c)){
        if (blockSize >= 1000000){
            block->next = new OccBlock(block->position + blockSize);
            blockSize = 0;
            block = block->next;
            occurences->tail = block;
            currEntry = NULL;
        }

        if (!currEntry){
            block->head = new OccBlock::OccEntry(c);
            currEntry = block->head;
        } else if (currEntry->c > (unsigned char) c){
            if (block->head->c > (unsigned char) c){
                OccBlock::OccEntry* newEntry = new OccBlock::OccEntry(c);
                newEntry->next = block->head;
                block->head = newEntry;
            }
            currEntry = block->head;
        }
        while (currEntry->c != c){
            if (!currEntry->next){
                currEntry->next = new OccBlock::OccEntry(c);
            } else if (currEntry->next->c > (unsigned char) c){
                OccBlock::OccEntry* newEntry = new OccBlock::OccEntry(c);
                newEntry->next = currEntry->next;
                currEntry->next = newEntry;
            }
            currEntry = currEntry->next;
        }
        currEntry->occ++;

        blockSize++;
    } 
    occurences->print();
}


// Debugging
void OccIndex::OccBlock::OccEntry::print(){
    std::cout << "Character: " << c << " Occurrences: " << occ << std::endl;
}

void OccIndex::OccBlock::print(){
    std::cout << "Block distance: " << position << std::endl;
    OccEntry* entry = head;
    while (entry){
        entry->print();
        entry = entry->next;
    }
}

void OccIndex::print(){
    OccBlock* block = head;
    while (block){
        block->print();
        block = block->next;
    }
}
