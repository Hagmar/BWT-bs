#ifndef CTABLE_H
#define CTABLE_H

#include "occindex.h"

class CTable {
    public:
        class CharEntry {
            public:
                unsigned char c;
                unsigned int v;
                CharEntry* next;

                CharEntry(unsigned char, unsigned int);

                // Debugging
                void print();
        };

        CharEntry* head;

        CTable(OccIndex*);

        // Debugging
        void print();
};

#endif
