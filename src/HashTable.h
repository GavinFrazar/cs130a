#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "BST.h"

struct HashRow
{
    std::string word;
    unsigned int count;

    HashRow(const std::string& word)
        : word(word), count(1)
    {}
};

class HashTable
{
private:
protected:
    HashRow** table;
    unsigned int size;

    unsigned int hashKey(std::string word);

public:
    //ctors
    HashTable(unsigned int size);

    //dtor
    ~HashTable();

    //methods
    bool search(std::string word);

    void insert(std::string word);

    void delete_word(std::string word);

    void sort();

    void range(std::string word1, std::string word2);
};

#endif