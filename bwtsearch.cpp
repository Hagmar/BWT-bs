#include <iostream>
#include <fstream>
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

int main(int argc, char** argv){
    if (argc != 5){
        std::cerr << "Error, wrong number of arguments" << std::endl;
    } else {
        std::string mode = argv[1];
        std::string filename = argv[2];
        std::string index = argv[3];
        std::string pattern = argv[4];

        OccIndex* occIndex = new OccIndex();
        occIndex->createOccIndex(argv[2]);

        CTable* cTable = new CTable(occIndex);
        cTable->print();

        std::ifstream in(argv[2]);
        std::cout << occ('s', 9, occIndex, in) << std::endl;
    }
    return 0;
}
