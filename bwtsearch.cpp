#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include "bwtsearch.h"
#include "index.h"


// Performs BWT backward search for a pattern in the specified file, using a
// provided index
searchResult backwardSearch(const char* pattern, const char* filename, Index* index){
    searchResult result;
    result.first = 0;
    result.last = 0;

    std::ifstream in(filename);
    std::ifstream ixIn(index->indexFile, std::ifstream::binary);

    unsigned int i = std::strlen(pattern) - 1;
    unsigned char c = pattern[i];
    result.first = index->getC(c);
    result.last = index->getC(c + 1) - 1;
    unsigned int occurrences;
    while ((result.first <= result.last) && i){
        c = pattern[--i];
        occurrences = index->occ(c, result.first, in, ixIn);
        result.first = index->getC(c) + occurrences;
        result.last = index->getC(c) + index->occ(c, result.last+1, in, ixIn) - 1;
    }

    in.close();
    ixIn.close();
    return result;
}

// Interprets the results and prints output corresponding to the type of search
// performed
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

// Uses BWT decoding to determine which records the search results belong to
std::set<unsigned int>* findRecords(searchResult result,
        const char* filename, Index* index){
    std::ifstream in(filename);
    std::ifstream ixIn(index->indexFile);

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
        in.seekg(hit, in.beg);
        in.get(c);
        next = index->occ(c, hit, in, ixIn) + index->getC(c);
        // Step backward until the '[' character denones the end of the offset
        // mark
        while (c != '['){
            // Once we reach ']', the next characters are the record number
            if (c == ']'){
                reachedOffset = true;
            } else if (reachedOffset){
                record += (c-'0') * scale;
                scale *= 10;
            }
            in.seekg(next, in.beg);
            in.get(c);
            next = index->occ(c, next, in, ixIn) + index->getC(c);
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

        Index* index = new Index(filename, indexFile);

        searchResult result = backwardSearch(pattern, filename, index);

        interpretResults(result, mode, filename, index);
    }
    return 0;
}
