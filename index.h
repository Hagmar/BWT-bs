#ifndef INDEX_H
#define INDEX_H

#include <fstream>

#define BLOCKCAPACITY 2
#define BLOCKELEMENTS 128
#define BLOCKSIZE BLOCKELEMENTS * sizeof(unsigned int)

class Index {
    unsigned int cTable[BLOCKELEMENTS];

    public:
        const char* indexFile;

        unsigned int occ(unsigned char, unsigned int, std::istream&, std::istream&);
        unsigned int getC(unsigned char);
        unsigned int createOccIndex(std::istream&);
        void writeBlockToIndex(unsigned int[BLOCKELEMENTS], std::ofstream&);
        void generateCTable(unsigned int, std::istream&, std::istream&);

        Index(const char*, const char*);

        // Debugging
        void print();
};

#endif
