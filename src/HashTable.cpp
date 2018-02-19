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

unsigned long long HashTable::findRow(const std::string &word, unsigned int hash)
{
    auto index = hash;
    do {
        if (table[index] == nullptr || table[index]->word == word)
            break;
        else
            index = (index + 1) % this->size;
    } while (index != hash);

    return index;
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
    auto index = findRow(word, hash);
    HashRow*& row_found = this->table[index];
    if (row_found != nullptr)
        return row_found->word == word;
    else
        return false;
}

void HashTable::insert(const std::string &word)
{
    auto hash = hashKey(word);
    auto index = findRow(word, hash);
    HashRow*& target = this->table[index];
    if (target == nullptr)
        target = new HashRow(word, hash);
    else
        ++target->count;
}

void HashTable::delete_word(const std::string &word)
{
    //find either the matching word or an empty row
    auto hash = hashKey(word);
    auto target_row_index = findRow(word, hash);
    if (table[target_row_index] != nullptr)
    {
        if (table[target_row_index]->count > 1)
            --table[target_row_index]->count;
        else
        {
            delete table[target_row_index];
            table[target_row_index] = nullptr;
            //swap empty row with non-empty row of hash value of equal or less value than the empty row's index
            for (unsigned int i = (target_row_index + 1) % size; table[i] != nullptr; i = (i + 1) % this->size)
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

std::vector<std::string> HashTable::sort()
{
    std::vector<std::string> v;
    v.reserve(this->size);
    for (unsigned int i = 0; i < this->size; ++i)
    {
        if (this->table[i] != nullptr)
            v.push_back(this->table[i]->word);
    }
    std::sort(v.begin(), v.end());
    return v;
}

void HashTable::range(const std::string &word1, const std::string &word2)
{
    for (unsigned int i = 0; i < this->size; ++i)
        if (table[i] != nullptr && table[i]->word >= word1 && table[i]->word <= word2)
            std::cout << this->table[i]->word << '\n';
}

unsigned int HashTable::getSize()
{
    return this->size;
}
