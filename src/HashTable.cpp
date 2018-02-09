#include "HashTable.h"

unsigned int HashTable::hashKey(std::string word)
{
    unsigned int hash = 0;
    for (auto &character : word)
    {
        hash = hash * 15485863 + character;
    }
    return hash % this->size;
}

HashTable::HashTable(unsigned int size)
{
    this->size = size;
    this->table = new HashRow*[size]();
}

HashTable::~HashTable()
{
    delete[] this->table;
    this->size = 0;
}

bool HashTable::search(std::string word)
{
    auto hash = hashKey(word);
    auto index = hash;
    while (table[index] != nullptr && table[index]->word != word)
}

void HashTable::insert(std::string word)
{
    auto hash = hashKey(word);
    auto index = hash;
    while (table[index] != nullptr && table[index]->word != word)
        index = (index + 1) % size;

    if (table[index] == nullptr)
        table[index] = new HashRow(word);
    else
        ++table[index]->count;
}

void HashTable::delete_word(std::string word)
{
    auto hash = hashKey(word);
}

void HashTable::sort()
{

}

void HashTable::range(std::string word1, std::string word2)
{
}
