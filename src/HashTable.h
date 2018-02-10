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
    unsigned int hashKey(const std::string &word);
    HashRow*& findRow(const std::string &word, unsigned int hash);
public:
    //ctors
    HashTable(unsigned int size);

    //dtor
    ~HashTable();

    //methods
    bool search(const std::string &word);

    void insert(const std::string &word);

    void delete_word(const std::string &word);

    void sort();

    void range(const std::string &word1, const std::string &word2);
};

#endif