#include <iostream>
#include <fstream>
#include <vector>
#include "bwtencode.h"
#include "bucket.h"

void encode(const char* filename){
    std::ifstream in(filename, std::ifstream::ate);

    if (!in.is_open()){
        std::cerr << "Error: cannot open file " << filename << std::endl;
    } else {
        std::vector<bool> slVector = generateSLVector(in);
        in.seekg(0, in.beg);
        printSLVector(slVector);

        BucketSorter* bs = new BucketSorter();
        sortCharacters(bs, in);
    }
    in.close();
}

std::vector<bool> generateSLVector(std::istream& in){
    unsigned int filesize = in.tellg();
    std::vector<bool> slVector(filesize);

    in.seekg(0, in.beg);
    populateSLVector(&slVector, in);

    return slVector;
}

void populateSLVector(std::vector<bool>* slVectorPtr, std::istream& in){
    std::vector<bool>& slVector = *slVectorPtr;
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
}

void sortCharacters(BucketSorter* bs, std::istream& in){
    char c;
    unsigned int index;

    while (in.get(c)){
        index = in.tellg();
        bs->bucket((unsigned char) c, index);
    }
}

int main(int argc, char** argv){
    for (int i = 1; i < argc; i++){
        encode(argv[i]);
    }

    return 0;
}

// Debugging
void printSLVector(std::vector<bool> vector){
    for (int i = 0; i < vector.size(); i++){
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}
