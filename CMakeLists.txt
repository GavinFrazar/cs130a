cmake_minimum_required(VERSION 3.0)
project(proj01 C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z -Wall -Wextra -lstdc++fs")
endif()

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
    ./src
    )

add_executable(main ${SOURCES} ${HEADERS})

message("CMAKE_CXX_FLAGS SET = {CMAKE_CXX_FLAGS}")