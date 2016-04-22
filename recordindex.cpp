#include <iostream>
#include <map>
#include "recordindex.h"
#include "occindex.h"
#include "ctable.h"

RecordIndex::RecordIndex(){
    index = new std::map<unsigned int, unsigned int>;
}

// TODO
void RecordIndex::createIndex(OccIndex* occIndex, CTable* cTable,
        std::istream& in){
    in.clear();
    in.seekg(0, in.beg);

    char c;
    if (!in.get(c)){
        return;
    }

    unsigned int position = 0;
    unsigned int record;
    unsigned int next;
}

void RecordIndex::print(){
    std::map<unsigned int, unsigned int>::iterator it = index->begin();
    unsigned int k, v;
    for (; it != index->end(); it++){
        k = it->first;
        v = it->second;
        std::cout << "K: " << k << ", V: " << v << std::endl;
    }
}
