#ifndef BWTENCODE_H
#define BWTENCODE_H

#include "bucket.h"

void encode(const char*);
std::vector<bool> generateSLVector(std::istream&);
void populateSLVector(std::vector<bool>*, std::istream&);
void sortCharacters(BucketSorter*, std::istream&);

int main(int, char**);

// Debugging
void printSLVector(std::vector<bool>);

#endif
