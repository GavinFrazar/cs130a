#include "HashTable.h"

unsigned int HashTable::hashKey(const std::string &word)
{
    unsigned int hash = 0;
    for (auto &character : word)
    {
        hash = hash * 31 + character;
    }
    return hash % this->size;
}

HashRow*& HashTable::findRow(const std::string &word, unsigned int hash)
{
    auto index = hash;
    do {
        if (table[index] == nullptr || table[index]->word == word)
            return table[index];
        else
            index = (index + 1) % this->size;
    } while (index != hash);

    return table[index];
}

HashTable::HashTable(unsigned int size)
{
    this->size = size;
    this->table = new HashRow*[size]();
}

HashTable::~HashTable()
{
    for (unsigned int i = 0; i < this->size; ++i)
        delete this->table[i];
    delete[] this->table;
}

bool HashTable::search(const std::string &word)
{
    auto hash = hashKey(word);
    return (findRow(word, hash)->word == word);
}

void HashTable::insert(const std::string &word)
{
    auto hash = hashKey(word);
    HashRow*& target = findRow(word, hash);
    if (target == nullptr)
        target = new HashRow(word, hash);
    else
        ++target->count;
}

void HashTable::delete_word(const std::string &word)
{
    unsigned int target_row_index = hashKey(word);
    if (table[target_row_index] != nullptr)
    {
        if (table[target_row_index]->count > 1)
            --table[target_row_index]->count;
        else
        {
            delete table[target_row_index];
            table[target_row_index] = nullptr;
            //swap empty row with non-empty row of hash value of equal or less value than the empty row's index
            for (unsigned int i = (target_row_index + 1) % size; table[i] != nullptr; i = (i + 1) % size)
            {
                if ((i > target_row_index && (table[i]->hash <= target_row_index || table[i]->hash > i)) ||
                    (i < target_row_index && (table[i]->hash <= target_row_index && table[i]->hash > i)))
                {
                    table[target_row_index] = table[i];
                    table[i] = nullptr;
                    target_row_index = i;
                }
            }
        }
    }
}

void HashTable::sort()
{

}

void HashTable::range(const std::string &word1, const std::string &word2)
{
    for (unsigned int i = 0; i < this->size; ++i)
        if (table[i]->word >= word1 && table[i]->word <= word2)
            std::cout << this->table[i]->word << std::endl;
}
