CC=g++

all: bwtencode

bwtencode: bwtencode.cpp bwtencode.h bucket.o sdistlist.o
	$(CC) -o bwtencode bwtencode.cpp bucket.o sdistlist.o

sdistlist.o: sdistlist.cpp sdistlist.h bucket.h
	$(CC) -c sdistlist.cpp bucket.h

bucket.o: bucket.cpp bucket.h
	$(CC) -c bucket.cpp

clean:
	rm *.o
