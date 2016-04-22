#include <iostream>
#include <map>
#include "recordindex.h"

RecordIndex::RecordIndex(){
    index = new std::map<unsigned int, unsigned int>;
}

void RecordIndex::print(){
}
