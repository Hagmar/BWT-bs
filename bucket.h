#ifndef BUCKET_H
#define BUCKET_H

template <class T, class V>
class BucketSorter {
    template <class T2, class V2>
    class Bucket {
        template <class V3>
        class Node {
            public:
                V3 value;
                Node* next;

                Node(V3);
        };

        public:
            T2 identifier;
            Node<V2>* head;
            Node<V2>* tail;
            Bucket<T2, V2>* next;

            void insert(V2);
            void remove(V2);

            Bucket();
            Bucket(T2);
            ~Bucket();

            // Debugging
            void print();

        private:
            void Construct(T2);
    };
    protected:
        Bucket<T, V>* head;
    public:
        BucketSorter();
        ~BucketSorter();

        void bucket(T, V);

        // Debugging
        void print();
};

#endif
