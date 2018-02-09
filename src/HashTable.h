#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "BST.h"

struct HashRow
{
    std::string word;
    unsigned int count;
    unsigned int hash;

    HashRow(const std::string& word, unsigned int hash)
        : word(word), count(1), hash(hash)
    {}
};

class HashTable
{
private:
protected:
    HashRow** table;
    unsigned int size;

    //methods
    unsigned int hashKey(std::string word);
    HashRow*& findRow(std::string word, unsigned int hash);
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