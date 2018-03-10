#include <HashTable.h>
#include <vector>
#include <string>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

HashTable fooReturnTemporaryHashTable(const HashTable& table_arg)
{
    HashTable temp = table_arg;
    temp.insert("ANOTHER ONE");
    return temp;
}

TEST_CASE("Test HashTable copying")
{
    HashTable* table1 = new HashTable(150);
    for (int i = 0; i < 100; ++i)
    {
        std::vector<char> acc;
        for (int j = 0; j <= i; ++j)
            acc.push_back('A' + j % 26);

        std::string word(acc.begin(), acc.end());
        table1->insert(word);
    }

    SECTION("copy during initialization")
    {
        HashTable* table2 = new HashTable(*table1);
        const auto& sorted_output1 = table1->sort();
        const auto& sorted_output2 = table2->sort();
        REQUIRE(sorted_output1 == sorted_output2);
        REQUIRE(table2->getSize() == table1->getSize());
        delete table2;
        REQUIRE(table1->sort().size() > 0);
    }

    SECTION("copy using assignment")
    {
        HashTable* table2 = new HashTable(table1->getSize());
        *table2 = *table1;
        const auto& sorted_output1 = table1->sort();
        const auto& sorted_output2 = table2->sort();
        REQUIRE(sorted_output1 == sorted_output2);
        REQUIRE(table2->getSize() == table1->getSize());
        delete table2;
        REQUIRE(table1->sort().size() > 0);
    }

    SECTION("Self-Assignment")
    {
        HashTable* table2 = new HashTable(*table1);
        *table2 = *table2;
        REQUIRE(table2->getSize() == table1->getSize());
        delete table2;
        REQUIRE(table1->sort().size() > 0);
    }

    SECTION("Move test")
    {
        HashTable* table2 = new HashTable(table1->getSize());
        *table2 = fooReturnTemporaryHashTable(*table1);
        REQUIRE(table1->getSize() > 0);
        REQUIRE(table2->search("ANOTHER ONE") == true);
        delete table2;
        REQUIRE(table1->sort().size() > 0);
    }
}