#ifndef INDEX_H
#define INDEX_H

#include <fstream>
#include "occindex.h"
#include "ctable.h"

class Index {
    OccIndex* occIndex;
    unsigned int cTable[256];

    public:
        const char* indexFile;

        unsigned int occ(unsigned char, unsigned int, std::istream&, std::istream&);
        unsigned int getC(unsigned char);
        void generateCTable(std::istream&);

        Index(const char*, const char*);

        // Debugging
        void print();
};

#endif
