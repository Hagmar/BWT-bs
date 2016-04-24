#ifndef BWTSEARCH_H
#define BWTSEARCH_H

#include <set>
#include "index.h"

struct searchResult {
    unsigned int first;
    unsigned int last;
};

searchResult backwardSearch(const char*, const char*, const char*, Index*);
void interpretResults(searchResult, const char*, const char*, Index*);
std::set<unsigned int>* findRecords(searchResult, const char*, Index*);

int main(int, char**);

#endif
