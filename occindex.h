#ifndef OCCINDEX_H
#define OCCINDEX_H

#include <fstream>
#include <map>

#define BLOCKSIZE 100000

class OccIndex {
    public:
        class OccBlock {
            public:
                unsigned int position;
                OccBlock* next;

                std::map<unsigned char, unsigned int> occurrences;

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
