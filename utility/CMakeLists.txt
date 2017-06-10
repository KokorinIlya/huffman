cmake_minimum_required(VERSION 2.8)

project(UTILITY)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O2 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()


include_directories(${UTILITY_DIR})
include_directories(header)
include_directories(${HUFFMAN_LIB_SOURCE_DIR}/header)

add_executable(utility
                main.cpp
                header/myFileReader.h
                header/myFileWriter.h
                header/print.h
                header/read.h
		header/workingWithFilesExceptions.h
               	myFileReader.cpp
               	myFileWriter.cpp
		print.cpp
		read.cpp)

install(TARGETS utility DESTINATION bin)
target_link_libraries(utility lib)
