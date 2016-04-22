#ifndef OCCINDEX_H
#define OCCINDEX_H

#include <fstream>

#define BLOCKSIZE 100000

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
        unsigned int occ(unsigned char, unsigned int, std::istream&);
        OccBlock* getIndexBlock(unsigned int);

        OccIndex();
        ~OccIndex();

        // Debugging
        void print();
};

#endif
