#include <iostream>
#include <fstream>
#include "occindex.h"

OccIndex::OccBlock::OccEntry::OccEntry(unsigned char character){
    c = character;
    occ = 0;
    next = NULL;
}

OccIndex::OccBlock::OccEntry::OccEntry(OccEntry* entry){
    c = entry->c;
    occ = entry->occ;
    next = NULL;
}

OccIndex::OccBlock::OccBlock(unsigned int pos){
    position = pos;
    head = NULL;
    next = NULL;
}

OccIndex::OccBlock::OccBlock(unsigned int pos, OccBlock* block){
    position = pos;
    next = NULL;

    OccEntry* entry = block->head;
    if (entry){
        head = new OccEntry(entry);
        entry = entry->next;
        OccEntry* lastEntry = head;
        while (entry){
            lastEntry->next = new OccEntry(entry);
            lastEntry = lastEntry->next;
            entry = entry->next;
        }
    }
}

OccIndex::OccBlock::~OccBlock(){
    OccEntry* entry = head;
    while (entry){
        entry = head->next;
        delete head;
        head = entry;
    }
}

OccIndex::OccIndex(){
    head = new OccBlock(BLOCKSIZE);
    tail = head;
}

OccIndex::~OccIndex(){
    OccBlock* block = head;
    while (block){
        block = head->next;
        delete head;
        head = block;
    }
}

unsigned int OccIndex::OccBlock::occInBlock(unsigned char c){
    OccEntry* entry = head;
    while (entry->c != c){
        entry = entry->next;
    }
    return entry->occ;
}

void OccIndex::createOccIndex(std::istream& in){
    OccBlock* block = head;
    OccBlock::OccEntry* currEntry = NULL;
    unsigned int blockSize = 0;

    char c;
    while (in.get(c)){
        if (blockSize >= BLOCKSIZE){
            block->next = new OccBlock(block->position + blockSize, block);
            blockSize = 0;
            block = block->next;
            tail = block;
            currEntry = block->head;
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
}

unsigned int OccIndex::occ(unsigned char c, unsigned int q, std::istream& in){
    OccBlock* block = getIndexBlock(c, q);

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

OccIndex::OccBlock* OccIndex::getIndexBlock(unsigned char c, unsigned int q){
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
