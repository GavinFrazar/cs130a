#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

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
    unsigned long long size;
    HashRow** table;

    //methods
    unsigned int hashKey(const std::string &word);
    unsigned long long findRow(const std::string &word, unsigned int hash);
public:
    //ctors
    HashTable(unsigned int size);

    //dtor
    ~HashTable();

    //methods
    bool search(const std::string &word);

    void insert(const std::string &word);

    void delete_word(const std::string &word);

    std::vector<std::string> sort();

    void range(const std::string &word1, const std::string &word2);

    unsigned int getSize();
};

#endif