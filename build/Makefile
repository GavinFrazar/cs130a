#variables
FLAGS=-c -Wall -std=c++17

all: main

main: main.o BST.o HashTable.o
	g++ -o main main.o BST.o HashTable.o -lstdc++fs

main.o: ../src/main.cpp
	g++ $(FLAGS) ../src/main.cpp

BST.o: ../src/BST.cpp
	g++ $(FLAGS) ../src/BST.cpp

HashTable.o: ../src/HashTable.cpp
	g++ $(FLAGS) ../src/HashTable.cpp

clean:
	rm -rf *.o main *~ sort_output.txt
