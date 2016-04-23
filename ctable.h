#ifndef CTABLE_H
#define CTABLE_H

#include <map>
#include "occindex.h"

class CTable {
    public:
        std::map<unsigned char, unsigned int> table;

        unsigned int getC(unsigned char);

        CTable(OccIndex*);

        // Debugging
        void print();
};

#endif
