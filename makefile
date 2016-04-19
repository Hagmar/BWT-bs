CC=g++

all: bwtsearch bwtencode

bwtsearch: bwtsearch.cpp bwtsearch.h
	$(CC) -o bwtsearch bwtsearch.cpp

bwtencode: bwtencode.cpp bwtencode.h bucket.o sdistlist.o
	$(CC) -o bwtencode bwtencode.cpp bucket.o sdistlist.o

sdistlist.o: sdistlist.cpp sdistlist.h bucket.h
	$(CC) -c sdistlist.cpp bucket.h

bucket.o: bucket.cpp bucket.h
	$(CC) -c bucket.cpp

clean:
	rm *.o
