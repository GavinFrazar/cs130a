cmake_minimum_required(VERSION 3.0)
project(main C CXX)

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

add_executable(main ${SOURCES} ${HEADERS})
target_include_directories(main PRIVATE src)

if (UNIX)
    target_link_libraries(main stdc++fs)
endif(UNIX)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

enable_testing(true)

# BST tests
add_executable(BSTcopy tests/BSTcopy.cpp src/BST.cpp)
target_link_libraries(BSTcopy Catch)
target_include_directories(BSTcopy PRIVATE src ${CATCH_INCLUDE_DIR})
add_test(TestBSTcopy BSTcopy)

# HashTable tests
add_executable(HashTablecopy tests/HashTablecopy.cpp src/HashTable.cpp)
target_link_libraries(HashTablecopy Catch)
target_include_directories(HashTablecopy PRIVATE src ${CATCH_INCLUDE_DIR})
add_test(TestHashTablecopy HashTablecopy)

set_tests_properties(
    TestBSTcopy
    TestHashTablecopy
    PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed"
)