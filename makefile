CC=g++

all: bwtsearch bwtencode

debug: CCFLAGS += -g3
debug: clean all

bwtsearch: bwtsearch.cpp bwtsearch.h index.o
	$(CC) $(CCFLAGS) -o bwtsearch bwtsearch.cpp index.o

index.o: index.cpp index.h
	$(CC) $(CCFLAGS) -c index.cpp



bwtencode: bwtencode.cpp bwtencode.h bucket.o sdistlist.o
	$(CC) $(CCFLAGS) -o bwtencode bwtencode.cpp bucket.o sdistlist.o

sdistlist.o: sdistlist.cpp sdistlist.h bucket.h
	$(CC) $(CCFLAGS) -c sdistlist.cpp

bucket.o: bucket.cpp bucket.h
	$(CC) $(CCFLAGS) -c bucket.cpp

clean:
	rm *.o
