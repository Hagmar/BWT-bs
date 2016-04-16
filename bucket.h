#ifndef BUCKET_H
#define BUCKET_H

class BucketSorter {
    class Bucket {
        class Node {
            public:
                unsigned int num;
                Node* next;

                Node(unsigned int);
                ~Node();
        };

        public:
            unsigned char character;
            Node* head;
            Node* tail;
            Bucket* next;

            void insert(unsigned int);
            void remove(unsigned int);

            Bucket();
            Bucket(unsigned char);
            ~Bucket();

        private:
            void Construct(unsigned char);
    };
    protected:
        Bucket* head;
    public:
        BucketSorter();
        ~BucketSorter();

        void bucket(unsigned char, unsigned int);
};

#endif
