#include <iostream>
#include <fstream>
#include <vector>
#include "bwtencode.h"

void encode(const char* filename){
    std::ifstream in(filename);

    if (!in.is_open()){
        std::cerr << "Error: cannot open file " << filename << std::endl;
    } else {
        std::vector<bool> slVector = generateSLVector(filename);
    }
    in.close();
}

std::vector<bool> generateSLVector(const char* filename){
    std::ifstream in(filename, std::ifstream::ate);
    unsigned int filesize = in.tellg();

    // Reset stream position to start of file
    std::vector<bool> slVector(filesize);
    in.seekg(0, in.beg);

    char c;
    char lastC;
    unsigned char slStatus;
    unsigned int offset = 0;
    unsigned int position;
    in.get(lastC);

    // Populate SL Vector
    while (in.get(c)){
        position = in.tellg();
        if (c != lastC){
            slStatus = ((unsigned char) lastC < (unsigned char) c);
            // Built-in offset of 2 because stream position is 2 ahead of lastC
            slVector[position-2] = slStatus;
            while (offset){
                slVector[position-offset-2] = slStatus;
                offset--;
            }
        } else {
            offset++;
        }

        lastC = c;
    }

    while (offset > 1){
        slVector[position-offset] = 0;
        offset--;
    }
    slVector[position-1] = 1;

    return slVector;
}

int main(int argc, char** argv){
    for (int i = 1; i < argc; i++){
        encode(argv[i]);
    }

    return 0;
}
