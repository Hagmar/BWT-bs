//TODO
#ifndef SDISTLIST_H
#define SDISTLIST_H

#include "bucket.h"

class SDistList{
    public:
        class Node {
            public:
                unsigned int distance;
                BucketSorter<unsigned char, unsigned int>* bs;
                Node* next;

                Node(unsigned int);
                ~Node();

                // Debugging
                void print();
        };

        Node* head;

        SDistList();
        ~SDistList();

        // Debugging
        void print();
};

#endif
