#include <iostream>
#include <map>
#include "ctable.h"
#include "occindex.h"

CTable::CTable(OccIndex* occIndex){
    table = std::map<unsigned char, unsigned int>();

    std::map<unsigned char, unsigned int>::iterator itEnd =
        occIndex->index.rbegin()->second.end();
    std::map<unsigned char, unsigned int>::iterator it =
        occIndex->index.rbegin()->second.begin();

    unsigned int previous = 0;
    for (; it != itEnd; it++){
        table[it->first] = previous;
        previous += it->second;
    }

    // An end-entry for retrieving the C-value of the last character
    table[-1] = previous;
}

unsigned int CTable::getC(unsigned char c, bool includeC){
    if (includeC){
        std::map<unsigned char, unsigned int>::iterator it;
        it = table.find(c);
        it++;
        return it->second;
    } else {
        return table[c];
    }
}

// Debugging
void CTable::print(){
    std::map<unsigned char, unsigned int>::iterator it;
    for (it = table.begin(); it != table.end(); it++){
        std::cout << "Character: " << it->first << " Previous: " << it->second << std::endl;
    }
}
