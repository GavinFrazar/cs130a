cmake_minimum_required(VERSION 3.0)
project(BST C CXX)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    ${SOURCES}
    src/main.cpp
    src/BST.cpp
    )

set(HEADERS
    ${HEADERS}
    src/BST.h
    )

include_directories(
    ${HEADERS}
    )

add_executable(main ${SOURCES} ${HEADERS})