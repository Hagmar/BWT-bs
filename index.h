#ifndef INDEX_H
#define INDEX_H

#include <fstream>

#define BLOCKELEMENTS 128
#define BLOCKSIZE (BLOCKELEMENTS * sizeof(unsigned int))
// If block capacity is the same as block size then index will be at most as
// big as the original file
#define BLOCKCAPACITY BLOCKSIZE

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
