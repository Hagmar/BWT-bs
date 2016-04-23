#ifndef OCCINDEX_H
#define OCCINDEX_H

#include <fstream>
#include <map>

#define BLOCKSIZE 10000

class OccIndex {
    public:
        std::map<unsigned int, std::map<unsigned char, unsigned int> > index;

        void createOccIndex(std::istream&);
        unsigned int occ(unsigned char, unsigned int, std::istream&);

        OccIndex();
        ~OccIndex();

        // Debugging
        void print();
};

#endif
