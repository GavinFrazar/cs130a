#include "HashTable.h"

std::size_t HashTable::hashKey(const std::string &word)
{
    unsigned int hash = 0;
    for (auto &character : word)
    {
        hash = hash * 31 + character;
    }
    return hash % this->size_;
}

std::size_t HashTable::findRow(const std::string &word, std::size_t hash)
{
    auto index = hash;
    do {
        if (table_[index] == nullptr || table_[index]->word == word)
            break;
        else
            index = (index + 1) % this->size_;
    } while (index != hash);

    return index;
}

HashTable::HashTable(std::size_t size)
{
    this->size_ = size;
    this->table_ = new HashRow*[size_](); //throws if you pass 0
}

HashTable::HashTable(const HashTable & rhs)
    : HashTable(rhs.size_)
{
    for (std::size_t i = 0; i < this->size_; ++i)
    {
        if (rhs.table_[i] != nullptr)
        {
            this->table_[i] = new HashRow(rhs.table_[i]->word, rhs.table_[i]->hash);
            this->table_[i]->count = rhs.table_[i]->count;
        }
    }
}

HashTable::HashTable(HashTable && rhs)
    : HashTable(0)
{
    swap(*this, rhs);
}

HashTable & HashTable::operator=(HashTable rhs)
{
    swap(*this, rhs);
    return *this;
}

HashTable::~HashTable()
{
    for (unsigned int i = 0; i < this->size_; ++i)
        delete this->table_[i];
    delete[] this->table_;
}

bool HashTable::search(const std::string &word)
{
    auto hash = hashKey(word);
    auto index = findRow(word, hash);
    HashRow*& row_found = this->table_[index];
    if (row_found != nullptr)
        return row_found->word == word;
    else
        return false;
}

void HashTable::insert(const std::string &word)
{
    auto hash = hashKey(word);
    auto index = findRow(word, hash);
    HashRow*& target = this->table_[index];
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
    if (table_[target_row_index] != nullptr)
    {
        if (table_[target_row_index]->count > 1)
            --table_[target_row_index]->count;
        else
        {
            delete table_[target_row_index];
            table_[target_row_index] = nullptr;
            //swap empty row with non-empty row of hash value of equal or less value than the empty row's index
            for (unsigned int i = (target_row_index + 1) % size_; table_[i] != nullptr; i = (i + 1) % this->size_)
            {
                if ((i > target_row_index && (table_[i]->hash <= target_row_index || table_[i]->hash > i)) ||
                    (i < target_row_index && (table_[i]->hash <= target_row_index && table_[i]->hash > i)))
                {
                    table_[target_row_index] = table_[i];
                    table_[i] = nullptr;
                    target_row_index = i;
                }
            }
        }
    }
}

std::vector<std::string> HashTable::sort()
{
    std::vector<std::string> v;
    v.reserve(this->size_);
    for (unsigned int i = 0; i < this->size_; ++i)
    {
        if (this->table_[i] != nullptr)
            v.push_back(this->table_[i]->word);
    }
    std::sort(v.begin(), v.end());
    return v;
}

void HashTable::range(const std::string &word1, const std::string &word2)
{
    for (unsigned int i = 0; i < this->size_; ++i)
        if (table_[i] != nullptr && table_[i]->word >= word1 && table_[i]->word <= word2)
            std::cout << this->table_[i]->word << '\n';
}

std::size_t HashTable::getSize()
{
    return this->size_;
}

void swap(HashTable & first, HashTable & second)
{
    using std::swap; //ADL
    swap(first.table_, second.table_);
    swap(first.size_, second.size_);
}
