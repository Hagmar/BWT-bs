#include <iostream>
#include <map>
#include <list>
#include "recordindex.h"
#include "occindex.h"
#include "ctable.h"

RecordIndex::RecordIndex(){
    index = std::map<unsigned int, unsigned int>();
}

void RecordIndex::createIndex(OccIndex* occIndex, CTable* cTable,
        std::istream& in){
    in.clear();
    in.seekg(0, in.beg);

    char c;
    if (!in.get(c)){
        return;
    }


    unsigned int start = 0;
    unsigned int position = 0;
    unsigned int record = 0;
    unsigned int scale = 1;
    unsigned int next;
    unsigned int characters = 0;
    std::list<unsigned int>::iterator it;

    next = occIndex->occ(c, position, in) + cTable->getC(c, false) - 1;
    while (c == '[' || c == ']' || (c >= '0' && c <= '9')){
        in.seekg(next, in.beg);
        in.get(c);
        start = next;
        next = occIndex->occ(c, next, in) + cTable->getC(c, false) - 1;
    }
    std::list<unsigned int> positions (1, start);

    while (next != start){
        in.seekg(next, in.beg);
        in.get(c);
        next = occIndex->occ(c, next, in) + cTable->getC(c, false) - 1;
    }
    return;

    while (true){
        while (c != ']'){
            if (next == start){
                for (it = positions.begin(); it != positions.end(); it++){
                    index[*it] = index[start];
                }
                return;
            }
            in.seekg(next, in.beg);
            in.get(c);
            if (++characters > RECORDINTERVAL){
                positions.push_front(next);
                characters = 0;
            }
            next = occIndex->occ(c, next, in) + cTable->getC(c, false) - 1;
        }
        in.seekg(next, in.beg);
        in.get(c);
        next = occIndex->occ(c, next, in) + cTable->getC(c, false) - 1;
        while (c != '['){
            record += (c-'0') * scale;
            scale *= 10;
            in.seekg(next, in.beg);
            in.get(c);
            next = occIndex->occ(c, next, in) + cTable->getC(c, false) - 1;
        }
        for (it = positions.begin(); it != positions.end(); it++){
            index[*it] = record;
        }
        positions.clear();
        record = 0;
        scale = 1;
        characters = -1;
    }
}

void RecordIndex::print(){
    std::map<unsigned int, unsigned int>::iterator it = index.begin();
    unsigned int k, v;
    for (; it != index.end(); it++){
        k = it->first;
        v = it->second;
        std::cout << "K: " << k << ", V: " << v << std::endl;
    }
}
