#ifndef OCCINDEX_H
#define OCCINDEX_H

class OccIndex {
    public:
        class OccBlock {
            public:
                class OccEntry {
                    public:
                        unsigned char c;
                        unsigned int occ;
                        OccEntry* next;

                        OccEntry(unsigned char);

                        // Debugging
                        void print();
                };

                unsigned int position;
                OccEntry* head;
                OccBlock* next;

                OccBlock(unsigned int);

                // Debugging
                void print();
        };

        OccBlock* head;
        OccBlock* tail;

        void createOccIndex(const char*);

        OccIndex();
        ~OccIndex();

        // Debugging
        void print();
};

#endif
