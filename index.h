#ifndef INDEX_H
#define INDEX_H

#include <fstream>

#define BLOCKSIZE 1024

class Index {
    unsigned int cTable[128];

    public:
        const char* indexFile;

        unsigned int occ(unsigned char, unsigned int, std::istream&, std::istream&);
        unsigned int getC(unsigned char);
        void createOccIndex(std::istream&);
        void writeBlockToIndex(unsigned int[128], std::ofstream&);
        void generateCTable(std::istream&);

        Index(const char*, const char*);

        // Debugging
        void print();
};

#endif
