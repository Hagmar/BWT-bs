#include <iostream>
#include <fstream>
#include <vector>
#include "bwtencode.h"

void encode(const char* filename){
    std::ifstream in(filename);

    if (!in.is_open()){
        std::cerr << "Error: cannot open file " << filename << std::endl;
    } else {
        std::vector<bool> slArray = generateSLArray(filename);
    }
    in.close();
}

std::vector<bool> generateSLArray(const char* filename){
    std::ifstream in(filename, std::ifstream::ate);
    unsigned int filesize = in.tellg();
    in.close();

    std::vector<bool> slArray(filesize);
    return slArray;
}

int main(int argc, char** argv){
    for (int i = 1; i < argc; i++){
        encode(argv[i]);
    }

    return 0;
}
