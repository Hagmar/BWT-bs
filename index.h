#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include "occindex.h"
#include "ctable.h"

class Index {
    OccIndex* occIndex;
    CTable* cTable;

    public:
        const char* indexFile;

        unsigned int occ(unsigned char, unsigned int, std::istream&, std::istream&);
        unsigned int getC(unsigned char);

        Index(const char*, const char*);

        // Debugging
        void printAll();
};

#endif
