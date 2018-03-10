#include <BST.h>
#include <vector>
#include <string>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

BST fooReturnTemporaryBST(const BST& tree_arg)
{
    BST temp = tree_arg;
    temp.insert("ANOTHER ONE");
    return temp;
}

TEST_CASE("Test BST copying")
{
    BST* tree1 = new BST();
    for (int i = 0; i < 100; ++i)
    {
        std::vector<char> acc;
        for (int j = 0; j <= i; ++j)
            acc.push_back('A' + j % 26);

        std::string word(acc.begin(), acc.end());
        tree1->insert(word);
    }

    SECTION("copy during initialization")
    {
        BST* tree2 = new BST(*tree1);
        const auto& sorted_output1 = tree1->sort();
        const auto& sorted_output2 = tree2->sort();
        REQUIRE(sorted_output1 == sorted_output2);
        REQUIRE(tree2->getSize() == tree1->getSize());
        delete tree2;
        REQUIRE(tree1->sort().size() > 0);
    }

    SECTION("copy using assignment")
    {
        BST* tree2 = new BST();
        *tree2 = *tree1;
        const auto& sorted_output1 = tree1->sort();
        const auto& sorted_output2 = tree2->sort();
        REQUIRE(sorted_output1 == sorted_output2);
        REQUIRE(tree2->getSize() == tree1->getSize());
        delete tree2;
        REQUIRE(tree1->sort().size() > 0);
    }

    SECTION("Self-Assignment")
    {
        BST* tree2 = new BST(*tree1);
        *tree2 = *tree2;
        REQUIRE(tree2->getSize() == tree1->getSize());
        delete tree2;
        REQUIRE(tree1->sort().size() > 0);
    }

    SECTION("Move test")
    {
        BST* tree2 = new BST();
        *tree2 = fooReturnTemporaryBST(*tree1);
        REQUIRE(tree1->getSize() > 0);
        REQUIRE(tree2->getSize() == tree1->getSize() + 1);
        REQUIRE(tree2->search("ANOTHER ONE") == true);
        delete tree2;
        REQUIRE(tree1->sort().size() > 0);
    }
}