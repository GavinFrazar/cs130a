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
    std::size_t hash;

    HashRow(const std::string& word, std::size_t hash)
        : word(word), count(1), hash(hash)
    {}
};

class HashTable
{
private:
protected:
    std::size_t size_;
    HashRow** table_;

    //methods
    std::size_t hashKey(const std::string &word);
    std::size_t findRow(const std::string &word, std::size_t hash);
public:
    //ctors
    HashTable() =delete;
    HashTable(std::size_t size);

    //copy ctor
    HashTable(const HashTable& rhs);

    //move ctor
    HashTable(HashTable && rhs);

    //assignment overload
    HashTable & operator= (HashTable rhs);

    //dtor
    ~HashTable();

    //swap
    friend void swap(HashTable& first, HashTable& second);

    //methods
    bool search(const std::string &word);

    void insert(const std::string &word);

    void delete_word(const std::string &word);

    std::vector<std::string> sort();

    void range(const std::string &word1, const std::string &word2);

    std::size_t getSize();
};

#endif