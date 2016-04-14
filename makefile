CC=g++

all: bwtencode

bwtencode: bwtencode.cpp bwtencode.h
	$(CC) -o bwtencode bwtencode.cpp

clean:
	rm *.o
