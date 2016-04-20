#include <iostream>
#include <fstream>
#include <cstring>
#include "bwtsearch.h"
#include "occindex.h"
#include "ctable.h"

unsigned int occ(unsigned char c, unsigned int q, OccIndex* occIndex,
        std::istream& in){
    OccIndex::OccBlock* block = getIndexBlock(c, q, occIndex);

    unsigned int occurrences = 0;
    unsigned int i = 0;

    in.clear();
    if (block){
        in.seekg(block->position, in.beg);
        i = block->position;
        occurrences = block->occInBlock(c);
    } else {
        in.seekg(0, in.beg);
    }

    char readChar;
    for (; i <= q; i++){
        if (!in.get(readChar)){
            break;
        }
        if (c == readChar){
            occurrences++;
        }
    }
    return occurrences;
}

// TODO Segfaults on empty pattern
searchResult backwardSearch(const char* pattern, const char* filename,
        OccIndex* index, CTable* cTable){
    searchResult result;
    result.first = 0;
    result.last = 0;

    std::ifstream in(filename);

    unsigned int i = std::strlen(pattern) - 1;
    unsigned char c = pattern[i];
    result.first = cTable->getC(c);
    result.last = cTable->getC(c+1) - 1;

    while ((result.first <= result.last) && i){
        c = pattern[--i];
        result.first = cTable->getC(c) + occ(c, result.first-1, index, in);
        result.last = cTable->getC(c) + occ(c, result.last, index, in) - 1;
    }

    return result;
}

void interpretResults(searchResult result, const char* mode){
    if (!std::strcmp(mode, "-n")){
        if (result.last < result.first){
            std::cout << 0 << std::endl;
        } else {
            std::cout << result.last-result.first + 1 << std::endl;
        }
    } else {
    }
}

int main(int argc, char** argv){
    if (argc != 5){
        std::cerr << "Error, wrong number of arguments" << std::endl;
    } else {
        const char* mode = argv[1];
        const char* filename = argv[2];
        const char* index = argv[3];
        const char* pattern = argv[4];

        OccIndex* occIndex = new OccIndex();
        occIndex->createOccIndex(filename);

        CTable* cTable = new CTable(occIndex);

        searchResult result = backwardSearch(pattern, filename, occIndex, cTable);

        interpretResults(result, mode);
    }
    return 0;
}
