#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include "occindex.h"
#include "ctable.h"
#include "recordindex.h"

class Index {
    OccIndex* occIndex;
    CTable* cTable;
    RecordIndex* recordIndex;

    public:
        unsigned int occ(unsigned char, unsigned int, std::istream&);
        unsigned int getC(unsigned char);

        Index(const char*);

        // Debugging
        void printAll();
};

#endif
