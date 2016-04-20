#include <iostream>
#include "ctable.h"
#include "occindex.h"

CTable::CharEntry::CharEntry(unsigned char character, unsigned int value){
    c = character;
    v = value;
    next = NULL;
}

CTable::CTable(OccIndex* occIndex){
    OccIndex::OccBlock::OccEntry* entry = occIndex->tail->head;
    head = NULL;

    CharEntry* charEntry;
    unsigned int c;
    unsigned int previous = 0;
    while (entry){
        c = entry->c;
        if (!head){
            head = new CharEntry(c, previous);
            charEntry = head;
        } else {
            charEntry->next = new CharEntry(c, previous);
            charEntry = charEntry->next;
        }
        previous += entry->occ;
        entry = entry->next;
    }
}

unsigned int CTable::getC(unsigned char c){
    CharEntry* entry = head;
    while (entry){
        if (entry->c >= c){
            return entry->v;
        }
        entry = entry->next;
    }
    return 0;
}

// Debugging
void CTable::CharEntry::print(){
    std::cout << "Character: " << c << " Previous: " << v << std::endl;
}

void CTable::print(){
    CharEntry* entry = head;
    while (entry){
        entry->print();
        entry = entry->next;
    }
}
