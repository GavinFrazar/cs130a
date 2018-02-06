#ifndef BST_H
#define BST_H

#include <string>
#include <vector>

struct Node
{
    std::string word;
    unsigned int counter;
    Node* left;
    Node* right;

    Node()
    { 
        this->counter = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(const std::string &word)
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
        Node* search_tree(const std::string& word);
    public:
        //ctor
        BST();

        //dtor
        ~BST();

        /*
        (b)
        A function for searching a word in the tree (the word may or may not exist).
        */
        bool search_word(const std::string& word);

        /*
        (c)
        A function for inserting a new word into the tree or increment the counter if it
        is already inserted.
        */
        void insert_word(const std::string &word);

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
        std::vector<std::string> range(std::string word1, std::string word2);
};
#endif