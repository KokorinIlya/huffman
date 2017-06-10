cmake_minimum_required(VERSION 2.8)

project(HUFFMAN_LIB)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O2 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()


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
