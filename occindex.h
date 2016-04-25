#ifndef OCCINDEX_H
#define OCCINDEX_H

#include <fstream>
#include <map>

#define BLOCKSIZE 512

class OccIndex {
    public:
        void createOccIndex(std::istream&, const char*);
        unsigned int occ(unsigned char, unsigned int, std::istream&, std::istream&);
        void writeBlockToIndex(unsigned int[128], std::ofstream&);

        OccIndex();
        ~OccIndex();

        // Debugging
        void print();
};

#endif
