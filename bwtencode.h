#ifndef BWTENCODE_H
#define BWTENCODE_H

#include "bucket.h"

void encode(const char*);
std::vector<bool> generateSLVector(std::istream&);
void populateSLVector(std::vector<bool>*, std::istream&);
void sortCharacters(BucketSorter<unsigned char, unsigned int>*, std::istream&);
void sDistanceBucket(BucketSorter<unsigned int, unsigned int>*, std::vector<bool>*);

int main(int, char**);

// Debugging
void printSLVector(std::vector<bool>);

#endif
