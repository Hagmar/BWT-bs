//TODO
#ifndef BWTENCODE_H
#define BWTENCODE_H

#include "bucket.h"
#include "sdistlist.h"

void encode(const char*);
std::vector<bool> generateSLVector(std::istream&);
void populateSLVector(std::vector<bool>*, std::istream&);
void sortCharacters(BucketSorter<unsigned char, unsigned int>*, std::istream&);
void sDistanceBucket(SDistList*,
        BucketSorter<unsigned char, unsigned int>*, std::vector<bool>*);
unsigned int calculateSDistance(unsigned int, std::vector<bool>*);
void bucketSSubstrings(BucketSorter<unsigned char, unsigned int>*,
        std::vector<bool>*);
void sortSSubstrings(BucketSorter<unsigned char, unsigned int>*,
        SDistList*);
void sortSBucket(BucketSorter<unsigned char, unsigned int>::
        Bucket<unsigned char, unsigned int>*,
        SDistList*);

int main(int, char**);

// Debugging
void printSLVector(std::vector<bool>);

#endif
