## huffman

# Description:

Simple C++ console utility, that performs file compressing and decompressing, using Huffman's algorithm

# Running:

*utility -compress fileFrom fileTo*

For compressing fileFrom and writing compressed data to fileTo

*utility -decompress fileFrom fileTo*

For decompressing fileFrom and writing decoded information to fileTo.

If fileFrom isn't file with compressed data, created by the application, deconding won't be done.

# Building

Run Cmake from the main directory for creating Makefile. After running Cmake, run make for finishing building.
