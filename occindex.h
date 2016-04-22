#ifndef OCCINDEX_H
#define OCCINDEX_H

#include <fstream>

#define BLOCKSIZE 1000000

class OccIndex {
    public:
        class OccBlock {
            public:
                class OccEntry {
                    public:
                        unsigned char c;
                        unsigned int occ;
                        OccEntry* next;

                        OccEntry(unsigned char);
                        OccEntry(OccEntry*);

                        // Debugging
                        void print();
                };

                unsigned int position;
                OccEntry* head;
                OccBlock* next;

                unsigned int occInBlock(unsigned char);

                OccBlock(unsigned int);
                OccBlock(unsigned int, OccBlock*);
                ~OccBlock();

                // Debugging
                void print();
        };

        OccBlock* head;
        OccBlock* tail;

        void createOccIndex(std::istream&);
        OccBlock* getIndexBlock(unsigned char, unsigned int);

        OccIndex();
        ~OccIndex();

        // Debugging
        void print();
};

#endif
