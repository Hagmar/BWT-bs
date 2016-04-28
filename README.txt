BWT Backward Search
Author: Magnus Hagmar
ZID: z5088131

The provided code implements BWT backward searching, as proposed by Paolo Ferragina and Giovanni Manzini, in a BWT encoded record file.

The main bottleneck of BWT backward search is counting the number of previous occurrences of a character in the file. The number of calls to the occurrence function (occ) is linear in the length of the search pattern when searching for any matching occurrences. In addition to this, one call to occ is required for every single step when backtracking from a result to determine which record it belongs to. This could result in hundreds or even thousands of calls. Clearly, a naive implementation of counting every character up to the desired point is not plausible.

This implementation generates an index file to speed up the occ function. This file is created by reading characters from the input file while keeping count of how many of each have occurred. Every time 392 (this seemingly random number will be explained later) characters have been read, the current occurrence counts for all characters up to that point are written to the index file as a block.

By utilizing an index constructed in this way, the number of characters which have to be read from the input file can be minimized. For example, if counting the number of 'A's which have occurred up until index 800, we could use the index to extract the number of 'A's up until index 2*392=784 and then simply check the remaining 16 characters to see if they are also 'A'. This is significantly faster than reading and observing all 800 characters up to that point.

The choice to read 392 characters into each block is not random, but rather the optimal choice considering the specifications and limitations of the task. First of all, there are only 98 characters which can occurr in the text file (tab, newline, carriage return and the visible ASCII characters 32-126). As such, the size of a block of occurrences written to disk is 98*4=392 bytes. The four comes from using an unsigned int to store the occurrences of each character. There is also a limitation that the index file is not permitted to exceed the original file in size. So if a block requires 392 bytes of disk space, then we need to include 392 bytes from the original file in each block. If less than 392 characters were counted for each block, then the index file would grow larger than the original file. It is possible to count more than 392 characters into each block, which would result in a smaller index file, but that would also result in a less accurate index and more characters having to be counted when running the occ function.



Description of the different files:

- index.h & index.cpp
    These files implement a an Index class, managing all usage of the occurrence index and C-table required for performing BWT backward search. Since the occurrence index only keeps track of 98 characters, a mapping is required from each character to its corresponding index in the 98 elements. An array "charMap" is used for this, indexed simply by the characters' numerical value and mapping to their new index in the compressed array.
    Creation of the index file as described above is managed by the Index class. The C-table is created by fetching the last occurrence block and then counting any remaining characters which haven't been included in the block. In addition to this, the C-table contains an extra entry after ASCII character 126. This is due to being required to look up C[c+1] in the backward search algorithm. Without this additional dummy character, this lookup would fail when c is '~', ASCII number 126. The charMap described above also contains dummy entries to prevent these failures.

- bwtsearch.h & bwtsearch.cpp
    These files implement the main function as well as the actual backward search algorithm and functions for interpreting the search results. The backward search is identical to Ferragina's and Manzini's algorithm, except for the detail that all indexing is zero-based to simplify indexing in arrays.
    The findRecords function implements a BWT decoder to step backwards through the original file in order to find the record to which a search result belongs to. This set of records is then either counted or printed, depending on the mode of searching.
