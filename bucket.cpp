#include <iostream>
#include "bucket.h"

BucketSorter::Bucket::Node::Node(unsigned int n){
    num = n;
    next = 0;
}

BucketSorter::Bucket::Bucket(){
    Construct(0);
}

BucketSorter::Bucket::Bucket(unsigned char c){
    Construct(c);
}

void BucketSorter::Bucket::Construct(unsigned char c){
    character = c;
    head = 0;
    tail = 0;
    next = 0;
}

BucketSorter::Bucket::~Bucket(){
    Node* n;

    while (head){
        n = head->next;
        delete head;
        head = n;
    }
}

BucketSorter::BucketSorter(){
    head = 0;
}

BucketSorter::~BucketSorter(){
    Bucket* b;

    while (head){
        b = head->next;
        delete head;
        head = b;
    }
}

void BucketSorter::Bucket::insert(unsigned int element){
    Node* newNode = new Node(element);
    if (!head){
        head = newNode;
    }
    if (tail){
        tail->next = newNode;
    }
    tail = newNode;
}

// TODO Untested
void BucketSorter::bucket(unsigned char c, unsigned int index){
    if (!head){
        head = new Bucket(c);
        head->insert(index);
        return;
    } else if (head->character == c){
        head->insert(index);
        return;
    } else if (head->character > c){
        Bucket* newBucket = new Bucket(c);
        newBucket->insert(index);
        newBucket->next = head;
        head = newBucket;
        return;
    }
    Bucket* b = head;

    // Find the bucket preceeding the correct one for c
    while (b->next){
        if (b->next->character >= c){
            break;
        } else {
            b = b->next;
        }
    }

    if (b->next){
        if (b->next->character != c){
            Bucket* newBucket = new Bucket(c);
            newBucket->next = b->next;
            b->next = newBucket;
            b = newBucket;
        } else {
            b = b->next;
        }
    } else {
        b->next = new Bucket(c);
        b = b->next;
    }

    b->insert(index);
}

// Debugging
void BucketSorter::Bucket::print(){
    Node* n = head;

    std::cout << "Bucket: " << character << std::endl;
    while (n){
        std::cout << n->num << " ";
        n = n->next;
    }
    std::cout << std::endl;
}

void BucketSorter::print(){
    Bucket* b = head;
    
    while (b){
        b->print();
        b = b->next;
    }
}
