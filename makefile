CC=g++

all: bwtencode

bwtencode: bwtencode.cpp bwtencode.h bucket.o
	$(CC) -o bwtencode bwtencode.cpp bucket.o

bucket.o: bucket.cpp bucket.h
	$(CC) -c bucket.cpp

clean:
	rm *.o
