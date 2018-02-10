cmake_minimum_required(VERSION 3.0)
project(proj01 C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    ${SOURCES}
    src/main.cpp
    src/BST.cpp
    src/HashTable.cpp
    )

set(HEADERS
    ${HEADERS}
    src/BST.h
    src/HashTable.h
    )

include_directories(
    ${HEADERS}
    )

add_executable(main ${SOURCES} ${HEADERS})