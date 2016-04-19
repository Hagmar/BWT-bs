CC=g++

all: bwtsearch bwtencode

debug: CCFLAGS += -g3
debug: clean all

bwtsearch: bwtsearch.cpp bwtsearch.h occindex.o ctable.o
	$(CC) $(CCFLAGS) -o bwtsearch bwtsearch.cpp occindex.o ctable.o

ctable.o: ctable.cpp ctable.h occindex.h
	$(CC) $(CCFLAGS) -c ctable.cpp

occindex.o: occindex.cpp occindex.h
	$(CC) $(CCFLAGS) -c occindex.cpp

bwtencode: bwtencode.cpp bwtencode.h bucket.o sdistlist.o
	$(CC) $(CCFLAGS) -o bwtencode bwtencode.cpp bucket.o sdistlist.o

sdistlist.o: sdistlist.cpp sdistlist.h bucket.h
	$(CC) $(CCFLAGS) -c sdistlist.cpp

bucket.o: bucket.cpp bucket.h
	$(CC) $(CCFLAGS) -c bucket.cpp

clean:
	rm *.o
