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
    unsigned int offset = 1;
    unsigned int position;
    in.get(lastC);

    // Populate SL Vector
    while (in.get(c)){
        position = in.tellg();
        if (c != lastC){
            slStatus = ((unsigned char) lastC < (unsigned char) c);
            slVector[position-1] = slStatus;
            while (offset > 1){
                slVector[position-offset] = slStatus;
                offset--;
            }
        } else {
            offset++;
        }

        lastC = c;
    }

    while (offset){
        slVector[position-offset] = 1;
        offset--;
    }

    return slVector;
}

int main(int argc, char** argv){
    for (int i = 1; i < argc; i++){
        encode(argv[i]);
    }

    return 0;
}
