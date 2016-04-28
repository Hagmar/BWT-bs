#ifndef INDEX_H
#define INDEX_H

#include <fstream>

// There are only 98 possible characters in the record files
#define BLOCKELEMENTS 98
#define BLOCKSIZE (BLOCKELEMENTS * sizeof(unsigned int))

// Manages the index used to speed up the search
class Index {
    private:
        unsigned int cTable[BLOCKELEMENTS+1];
        unsigned char charMap[128];

        void initializeCharMap();

    public:
        const char* indexFile;

        unsigned int occ(unsigned char, unsigned int, std::istream&, std::istream&);
        unsigned int getC(unsigned char);
        unsigned int createOccIndex(std::istream&);
        void writeBlockToIndex(unsigned int[BLOCKELEMENTS], std::ofstream&);
        void generateCTable(unsigned int, std::istream&, std::istream&);

        Index(const char*, const char*);
};

#endif
