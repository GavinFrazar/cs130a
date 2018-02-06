#ifndef BST_H
#define BST_H

#include <string>
#include <list>
#include <algorithm>

struct Node
{
    std::string word;
    unsigned int counter;
    Node* left;
    Node* right;

    Node()
    { 
        this->counter = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(const std::string &word)
        : Node()
    {
        this->word = word;
    }
};

class BST
{
    private:
    protected:
        Node* root;
        //deletes a tree
        void delete_tree(Node* root);
        Node* search_tree(std::string word);
        void to_lower(std::string& s);
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
        A function to sort the words in the tree lexicographically.
        */
        void sort_tree();

        /*
        (f)
        A function for doing a range search. The function takes as input two words. Given two
        words, the function should find all the words in between. The resulting words need not
        be sorted.
        */
        std::list<std::string> range(std::string word1, std::string word2);
};
#endif