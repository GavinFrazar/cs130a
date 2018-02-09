#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>
#include <algorithm>

struct Node
{
    std::string word;
    unsigned int count;
    Node* left;
    Node* right;

    Node(const std::string &word)
        : word(word),
        count(1),
        left(nullptr),
        right(nullptr)
    {}
};

class BST
{
    private:
    protected:
        //fields
        Node* root;
        unsigned long long unique_word_count;

        //methods
        void delete_tree(Node* root);
        Node* find_node(std::string word);
        void to_lower(std::string& s);
        void range(Node* root, std::string word1, std::string word2);
        void sort(Node* root);
    public:
        //ctor
        BST();

        //dtor
        ~BST();

        /*
        (b)
        A function for searching a word in the tree (the word may or may not exist).
        */
        bool search_word(std::string word);

        /*
        (c)
        A function for inserting a new word into the tree or increment the counter if it
        is already inserted.
        */
        void insert_word(std::string word);

        /*
        (d)
        A function for deleting a word from the tree if the counter reaches ZERO
        or decrementing the counter by one. Words that do not exist in tree should be ignored.
        */
        void delete_word(std::string word);

        /*
        (e)
        A function to print the words of the tree in lexicographically sorted order.
        */
        void sort();

        /*
        (f)
        A function for doing a range search. The function takes as input two words. Given two
        words, the function should find all the words in between. The resulting words need not
        be sorted.
        */
        void range(std::string word1, std::string word2);
};
#endif