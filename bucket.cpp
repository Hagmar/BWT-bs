#include <iostream>
#include "bucket.h"

template <class T, class V>
template <class T2, class V2>
template <class V3>
BucketSorter<T, V>::Bucket<T2, V2>::Node<V3>::Node(V3 n){
    value = n;
    next = NULL;
}

template <class T, class V>
template <class T2, class V2>
BucketSorter<T, V>::Bucket<T2, V2>::Bucket(){
    Construct(0);
}

template <class T, class V>
template <class T2, class V2>
BucketSorter<T, V>::Bucket<T2, V2>::Bucket(T2 c){
    Construct(c);
}

template <class T, class V>
template <class T2, class V2>
void BucketSorter<T, V>::Bucket<T2, V2>::Construct(T2 c){
    identifier = c;
    head = NULL;
    tail = NULL;
    next = NULL;
}

template <class T, class V>
template <class T2, class V2>
BucketSorter<T, V>::Bucket<T2, V2>::~Bucket(){
    Node<V>* n;

    while (head){
        n = head->next;
        delete head;
        head = n;
    }
}

template <class T, class V>
BucketSorter<T, V>::BucketSorter(){
    head = NULL;
}

template <class T, class V>
BucketSorter<T, V>::~BucketSorter(){
    Bucket<T, V>* b;

    while (head){
        b = head->next;
        delete head;
        head = b;
    }
}

template <class T, class V>
template <class T2, class V2>
void BucketSorter<T, V>::Bucket<T2, V2>::insert(V2 element){
    Node<V>* newNode = new Node<V>(element);
    if (!head){
        head = newNode;
    }
    if (tail){
        tail->next = newNode;
    }
    tail = newNode;
}

template <class T, class V>
template <class T2, class V2>
void BucketSorter<T, V>::Bucket<T2, V2>::remove(V2 element){
    Node<V>* node;
    Node<V>* lastNode = head;

    while (head->value == element){
        head = head->next;
        delete lastNode;
        lastNode = head;
    }
    if (!head){
        tail = NULL;
        return;
    }

    node = lastNode->next;
    while (node){
        if (node->value == element){
            lastNode->next = node->next;
            delete node;
            node = lastNode->next;
        } else {
            lastNode = node;
            node = node->next;
        }
    }
    tail = lastNode;
}

template <class T, class V>
void BucketSorter<T, V>::bucket(T c, V index){
    if (!head){
        head = new Bucket<T, V>(c);
        head->insert(index);
        return;
    } else if (head->identifier == c){
        head->insert(index);
        return;
    } else if (head->identifier > c){
        Bucket<T, V>* newBucket = new Bucket<T, V>(c);
        newBucket->insert(index);
        newBucket->next = head;
        head = newBucket;
        return;
    }
    Bucket<T, V>* b = head;

    // Find the bucket preceeding the correct one for c
    while (b->next){
        if (b->next->identifier >= c){
            break;
        } else {
            b = b->next;
        }
    }

    if (b->next){
        if (b->next->identifier != c){
            Bucket<T, V>* newBucket = new Bucket<T, V>(c);
            newBucket->next = b->next;
            b->next = newBucket;
            b = newBucket;
        } else {
            b = b->next;
        }
    } else {
        b->next = new Bucket<T, V>(c);
        b = b->next;
    }

    b->insert(index);
}

// Debugging
template <class T, class V>
template <class T2, class V2>
void BucketSorter<T, V>::Bucket<T2, V2>::print(){
    Node<V>* n = head;

    std::cout << "Bucket: " << identifier << std::endl;
    while (n){
        std::cout << n->value << " ";
        n = n->next;
    }
    std::cout << std::endl;
}

template <class T, class V>
void BucketSorter<T, V>::print(){
    Bucket<T, V>* b = head;
    
    while (b){
        b->print();
        b = b->next;
    }
}

template class BucketSorter<unsigned char, unsigned int>;
template class BucketSorter<unsigned int, unsigned int>;
