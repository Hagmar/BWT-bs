#ifndef CTABLE_H
#define CTABLE_H

#include <map>
#include "occindex.h"

class CTable {
    public:
        unsigned int table[256];

        unsigned int getC(unsigned char);

        CTable(std::istream&);

        // Debugging
        void print();
};

#endif
