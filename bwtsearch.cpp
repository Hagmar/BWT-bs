#include <iostream>
#include <fstream>
#include "bwtsearch.h"
#include "occindex.h"

int main(int argc, char** argv){
    if (argc != 5){
        std::cerr << "Error, wrong number of arguments" << std::endl;
    } else {
        std::string mode = argv[1];
        std::string filename = argv[2];
        std::string index = argv[3];
        std::string pattern = argv[4];

        OccIndex* occIndex = new OccIndex();
        occIndex->createOccIndex(argv[2]);
    }
    return 0;
}
