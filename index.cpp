#include <fstream>
#include "index.h"
#include "occindex.h"
#include "ctable.h"
#include "recordindex.h"

Index::Index(const char* filename){
    std::ifstream in(filename);

    occIndex = new OccIndex();
    occIndex->createOccIndex(in);
    cTable = new CTable(occIndex);
    recordIndex = new RecordIndex();
}

unsigned int Index::occ(unsigned char c, unsigned int q, std::istream& in){
    OccIndex::OccBlock* block = occIndex->getIndexBlock(c, q);

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

unsigned int Index::getC(unsigned char c){
    return cTable->getC(c);
}
