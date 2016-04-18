#include <iostream>
#include "sdistlist.h"

SDistList::Node::Node(unsigned int d){
    distance = d;
    bs = new BucketSorter<unsigned char, unsigned int>;
    next = 0;
}

SDistList::Node::~Node(){
    delete bs;
}

SDistList::SDistList(){
    head = new Node(1);
}

SDistList::~SDistList(){
    Node* node;
    while (head){
        node = head->next;
        delete head;
        head = node;
    }
}

void SDistList::Node::print(){
    std::cout << "Node: " << distance << std::endl;
    bs->print();
}

void SDistList::print(){
    std::cout << "S dist list:" << std::endl;
    Node* node = head;
    while (node){
        node->print();
        node = node->next;
    }
    std::cout << std::endl;
}
