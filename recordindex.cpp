#include <iostream>
#include <map>
#include "recordindex.h"

RecordIndex::RecordIndex(){
    index = new std::map<unsigned int, unsigned int>;
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
