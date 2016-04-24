#ifndef RECORDINDEX_H
#define RECORDINDEX_H

#include <map>
#include "occindex.h"
#include "ctable.h"

// For each entry in the index we need 4 bytes for they key and 4 for the
// value. This interval needs to be large enough to make sure the index file
// is small enough.
#define RECORDINTERVAL 10

class RecordIndex {
    std::map<unsigned int, unsigned int> index;

    public:
        void createIndex(OccIndex*, CTable*, std::istream&);

        RecordIndex();
        RecordIndex(OccIndex*, CTable*, std::istream&);
        ~RecordIndex();

        // Debugging
        void print();
};

#endif
