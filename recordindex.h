#ifndef RECORDINDEX_H
#define RECORDINDEX_H

#include <map>
#include "occindex.h"
#include "ctable.h"

class RecordIndex {
    std::map<unsigned int, unsigned int>* index;

    RecordIndex();
    ~RecordIndex();

    // Debugging
    void print();
};

#endif
