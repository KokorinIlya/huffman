cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_LIB)
include_directories(${HUFFMAN_LIB_DIR})
include_directories(header)

set(SOURCES 
		codeWord.cpp
		counter.cpp
		huffmanEncryptor.cpp
		huffmanDecryptor.cpp)
				
set(HEADERS 
			header/codeWord.h
			header/constantsAndTypes.h
			header/counter.h
			header/huffmanDecryptor.h
			header/huffmanEncryptor.h
			header/huffmanLibrary.h
			header/libraryExceptions.h)
			
add_library(lib ${SOURCES} ${HEADERS})
		
install (TARGETS lib DESTINATION lib)

install (FILES ${HEADERS} DESTINATION include/lib)
