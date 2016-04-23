#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include "bwtsearch.h"
#include "index.h"
#include "occindex.h"
#include "ctable.h"


// TODO Segfaults on empty pattern
searchResult backwardSearch(const char* pattern, const char* filename, Index* index){
    searchResult result;
    result.first = 0;
    result.last = 0;

    std::ifstream in(filename);

    unsigned int i = std::strlen(pattern) - 1;
    unsigned char c = pattern[i];
    result.first = index->getC(c, false);
    result.last = index->getC(c, true) - 1;
    unsigned char occurrences;
    while ((result.first <= result.last) && i){
        c = pattern[--i];
        if (result.first){
            occurrences = index->occ(c, result.first-1, in);
        } else {
            in.clear();
            in.seekg(0, in.beg);
            occurrences = in.get() == c;
        }
        result.first = index->getC(c, false) + occurrences;
        result.last = index->getC(c, false) + index->occ(c, result.last, in) - 1;
    }

    in.close();
    return result;
}

void interpretResults(searchResult result, const char* mode,
        const char* filename, Index* index){
    if (!std::strcmp(mode, "-n")){
        if (result.last < result.first){
            std::cout << 0 << std::endl;
        } else {
            std::cout << result.last-result.first + 1 << std::endl;
        }
    } else {
        bool listRecords = std::strcmp(mode, "-r");
        std::set<unsigned int>* records;
        records = findRecords(result, filename, index);
        if (listRecords){
            std::set<unsigned int>::iterator it = records->begin();
            while (it != records->end()){
                std::cout << '[' << *it++ << ']' << std::endl;
            }
        } else {
            std::cout << records->size() << std::endl;
        }
    }
}

std::set<unsigned int>* findRecords(searchResult result,
        const char* filename, Index* index){
    std::ifstream in(filename);
    unsigned int record;
    unsigned int scale;
    bool reachedOffset;
    unsigned int next;
    char c = 0;
    std::set<unsigned int>* records = new std::set<unsigned int>();
    for (unsigned int hit = result.first; hit <= result.last; hit++){
        reachedOffset = false;
        record = 0;
        scale = 1;
        in.seekg(hit);
        in.get(c);
        next = index->occ(c, hit, in) + index->getC(c, false) - 1;
        while (c != '['){
            if (c == ']'){
                reachedOffset = true;
            } else if (reachedOffset){
                record += (c-'0') * scale;
                scale *= 10;
            }
            in.seekg(next);
            in.get(c);
            next = index->occ(c, next, in) + index->getC(c, false) - 1;
        }
        records->insert(record);
    }
    return records;
}

int main(int argc, char** argv){
    if (argc != 5){
        std::cerr << "Error, wrong number of arguments" << std::endl;
    } else {
        const char* mode = argv[1];
        const char* filename = argv[2];
        const char* indexFile = argv[3];
        const char* pattern = argv[4];

        Index* index = new Index(filename);

        searchResult result = backwardSearch(pattern, filename, index);

        interpretResults(result, mode, filename, index);
    }
    return 0;
}
