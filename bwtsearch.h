#ifndef BWTSEARCH_H
#define BWTSEARCH_H

#include "occindex.h"

unsigned int occ(unsigned char, unsigned int, OccIndex*, std::istream&);
OccIndex::OccBlock* getIndexBlock(unsigned char, unsigned int, OccIndex*);

int main(int, char**);

#endif
