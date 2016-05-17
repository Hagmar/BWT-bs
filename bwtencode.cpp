//TODO
#include <iostream>
#include <fstream>
#include <vector>
#include "bwtencode.h"
#include "bucket.h"
#include "sdistlist.h"

void encode(const char* filename){
    std::ifstream in(filename, std::ifstream::ate);

    if (!in.is_open()){
        std::cerr << "Error: cannot open file " << filename << std::endl;
    } else {
        std::vector<bool> slVector = generateSLVector(in);
        in.clear();
        in.seekg(0, in.beg);

        BucketSorter<unsigned char, unsigned int>* bs =
            new BucketSorter<unsigned char, unsigned int>();
        sortCharacters(bs, in);

        in.clear();
        in.seekg(0, in.beg);
        SDistList* sDist = new SDistList();
        sDistanceBucket(sDist, bs, &slVector);

        bucketSSubstrings(bs, &slVector);
        bs->print();

        sortSSubstrings(bs, sDist);
        bs->print();
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

void sortCharacters(BucketSorter<unsigned char, unsigned int>* bs, std::istream& in){
    char c;
    unsigned int index;

    while (in.get(c)){
        index = in.tellg();
        // -1 because tell(g) points to the index of the next character
        bs->bucket((unsigned char) c, index-1);
    }
}

void sDistanceBucket(SDistList* sDist,
        BucketSorter<unsigned char, unsigned int>* bs,
        std::vector<bool>* slVectorPtr){
    BucketSorter<unsigned char, unsigned int>
        ::Bucket<unsigned char, unsigned int>* bucket = bs->head;
    BucketSorter<unsigned char, unsigned int>
        ::Bucket<unsigned char, unsigned int>
        ::Node<unsigned int>* node;
    SDistList::Node* sDistBucket = sDist->head;
    unsigned int distance;

    while (bucket){
        node = bucket->head;
        while (node){
            distance = calculateSDistance(node->value, slVectorPtr);
            if (distance){
                while (sDistBucket->distance != distance){
                    if (!sDistBucket->next){
                        sDistBucket->next = new SDistList::
                            Node(sDistBucket->distance+1);
                    }
                    sDistBucket = sDistBucket->next;
                }
                sDistBucket->bs->bucket(bucket->identifier, node->value);
                sDistBucket = sDist->head;
            }
            node = node->next;
        }
        bucket = bucket->next;
    }
}

unsigned int calculateSDistance(unsigned int index, std::vector<bool>* slVectorPtr){
    std::vector<bool>& slVector = *slVectorPtr;
    unsigned int distance = 0;

    while (index){
        distance++;
        if (slVector[--index]){
            return distance;
        }
    }

    return 0;
}

void bucketSSubstrings(BucketSorter<unsigned char, unsigned int>* bs,
        std::vector<bool>* slVectorPtr){
    std::vector<bool>& slVector = *slVectorPtr;

    BucketSorter<unsigned char, unsigned int>
        ::Bucket<unsigned char, unsigned int> *bucket = bs->head, *lastBucket;
    BucketSorter<unsigned char, unsigned int>
        ::Bucket<unsigned char, unsigned int>
        ::Node<unsigned int> *node, *lastNode = NULL;

    unsigned int index;
    while (bucket){
        node = bucket->head;
        while (node){
            index = node->value;
            if (!slVector[index]){
                if (node == bucket->head){
                    bucket->head = node->next;
                    delete node;
                    node = bucket->head;
                } else {
                    lastNode->next = node->next;
                    delete node;
                    node = lastNode->next;
                }
            } else {
                lastNode = node;
                node = node->next;
            }
        }
        bucket->tail = lastNode;

        if (!bucket->head){
            if (bucket == bs->head){
                bs->head = bucket->next;
                delete bucket;
                bucket = bs->head;
            } else {
                lastBucket->next = bucket->next;
                delete bucket;
                bucket = lastBucket->next;
            }
        } else {
            lastBucket = bucket;
            bucket = bucket->next;
        }
    }
}

void sortSSubstrings(BucketSorter<unsigned char, unsigned int>* sStrings,
        SDistList* sDist){
    BucketSorter<unsigned char, unsigned int>
        ::Bucket<unsigned char, unsigned int> *bucket = sStrings->head;

    while (bucket){
        if (bucket->head != bucket->tail){
            sortSBucket(bucket, sDist);
        }
        bucket = bucket->next;
    }
}

void sortSBucket(BucketSorter<unsigned char, unsigned int>::
        Bucket<unsigned char, unsigned int>* bucket,
        SDistList* sDist){
    BucketSorter<unsigned char, unsigned int>
        ::Bucket<unsigned char, unsigned int>
        ::Node<unsigned int> *node, *sStringNode, *lastSStringNode;
    SDistList::Node* sDistNode = sDist->head;
    BucketSorter<unsigned char, unsigned int>
        ::Bucket<unsigned char, unsigned int>* sDistBucket;

    unsigned int sortIndex = 0;
    unsigned int sorted = 0;
    unsigned int sDistIndex;

    BucketSorter<unsigned int, unsigned int>* sortedBucketSorter =
        new BucketSorter<unsigned int, unsigned int>();
    BucketSorter<unsigned int, unsigned int>::
        Bucket<unsigned int, unsigned int> *sortedBucket, *sortedBucketIterator;
    BucketSorter<unsigned int, unsigned int>::
        Bucket<unsigned int, unsigned int>::
        Node<unsigned int> *sortedBucketNode, *sortedBucketIteratorNode;

    while (sDistNode){
        std::cout << "Using s-list with distance " << sDistNode->distance << std::endl;
        sDistBucket = sDistNode->bs->head;
        while (sDistBucket){
            sDistBucket->print();
            node = sDistBucket->head;
            while (node){
                sDistIndex = node->value;
                sStringNode = bucket->head;
                while (sStringNode){
                    if (sDistIndex == sStringNode->value + sDistNode->distance){
                        std::cout << "Sorting "<<sStringNode->value<<" into "<<sortIndex<<std::endl;
                        sortedBucketSorter->bucket(sortIndex, sStringNode->value);
                        sorted++;
                        if (sStringNode == bucket->head){
                            bucket->head = sStringNode->next;
                        } else {
                            lastSStringNode->next = sStringNode->next;
                        }
                        delete sStringNode;
                        break;
                    }
                    lastSStringNode = sStringNode;
                    sStringNode = sStringNode->next;
                }
                node = node->next;
            }
            sortIndex += sorted;
            sorted = 0;
            sDistBucket = sDistBucket->next;
        }
        sDistNode = sDistNode->next;
    }

    sortedBucket = sortedBucketSorter->head;
    while (sortedBucket){
        if (sortedBucket->head != sortedBucket->tail){
            sortedBucketIterator = sortedBucketSorter->head;
            while (sortedBucketIterator){
                if (sortedBucketIterator != sortedBucket){
                    sortedBucketIteratorNode = sortedBucketIterator->head;
                    while (sortedBucketIteratorNode){
                        sortedBucketNode = sortedBucket->head;
                        while (sortedBucketNode){
                            sortedBucketNode = sortedBucketNode->next;
                        }
                    }
                    sortedBucketIteratorNode = sortedBucketIteratorNode->next;
                }
                sortedBucketIterator = sortedBucketIterator->next;
            }
        }
        sortedBucket = sortedBucket->next;
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
