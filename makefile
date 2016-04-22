CC=g++

all: bwtsearch bwtencode

debug: CCFLAGS += -g3
debug: clean all

bwtsearch: bwtsearch.cpp bwtsearch.h index.o occindex.o ctable.o recordindex.o
	$(CC) $(CCFLAGS) -o bwtsearch bwtsearch.cpp index.o occindex.o ctable.o recordindex.o

index.o: index.cpp index.h occindex.h ctable.h recordindex.h
	$(CC) $(CCFLAGS) -c index.cpp

occindex.o: occindex.cpp occindex.h
	$(CC) $(CCFLAGS) -c occindex.cpp

ctable.o: ctable.cpp ctable.h occindex.h
	$(CC) $(CCFLAGS) -c ctable.cpp

recordindex.o: recordindex.cpp recordindex.h occindex.h ctable.h
	$(CC) $(CCFLAGS) -c recordindex.cpp



bwtencode: bwtencode.cpp bwtencode.h bucket.o sdistlist.o
	$(CC) $(CCFLAGS) -o bwtencode bwtencode.cpp bucket.o sdistlist.o

sdistlist.o: sdistlist.cpp sdistlist.h bucket.h
	$(CC) $(CCFLAGS) -c sdistlist.cpp

bucket.o: bucket.cpp bucket.h
	$(CC) $(CCFLAGS) -c bucket.cpp

clean:
	rm *.o
