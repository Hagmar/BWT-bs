#ifndef BWTSEARCH_H
#define BWTSEARCH_H

#include <set>
#include "occindex.h"
#include "ctable.h"

struct searchResult {
    unsigned int first;
    unsigned int last;
};

unsigned int occ(unsigned char, unsigned int, OccIndex*, std::istream&);
OccIndex::OccBlock* getIndexBlock(unsigned char, unsigned int, OccIndex*);

searchResult backwardSearch(const char*, const char*, OccIndex*, CTable*);
void interpretResults(searchResult, const char*, const char*, OccIndex*,
        CTable*);
std::set<unsigned int>* findRecords(searchResult, const char*, OccIndex*,
        CTable*);

int main(int, char**);

#endif
