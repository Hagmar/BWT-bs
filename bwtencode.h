#ifndef BWTENCODE_H
#define BWTENCODE_H

void encode(const char*);
std::vector<bool> generateSLVector(std::istream&);
void populateSLVector(std::vector<bool>*, std::istream&);

int main(int, char**);

// Debugging
void printSLVector(std::vector<bool>);

#endif
