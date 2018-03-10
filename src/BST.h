#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>
#include <vector>

struct Node
{
    std::string word;
    unsigned int count;
    Node* left;
    Node* right;
    Node(const std::string& word)
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
    Node* root_;
    std::size_t size_;

    //methods
    void deleteTree(Node* root);
    void range(Node* root, const std::string & word1, const std::string & word2);
    void sort(Node* root, std::vector<std::string>& output);
    void deepCopy(Node*& first, Node* const & second);
public:
    //ctor
    BST();

    //copy ctor
    BST(const BST& rhs);
    
    //move ctor
    BST(BST && rhs);

    //assignment op
    BST & operator=(BST rhs);

    //dtor
    ~BST();

    //swap buddy
    friend void swap(BST& first, BST& second);

    /*
    (b)
    A function for searching a word in the tree (the word may or may not exist).
    */
    bool search(const std::string & word);

    /*
    (c)
    A function for inserting a new word into the tree or increment the counter if it
    is already inserted.
    */
    void insert(const std::string& word);

    /*
    (d)
    A function for deleting a word from the tree if the counter reaches ZERO
    or decrementing the counter by one. Words that do not exist in tree should be ignored.
    */
    void delete_word(const std::string & word);

    /*
    (e)
    A function to print the words of the tree in lexicographically sorted order.
    */
    std::vector<std::string> sort();

    /*
    (f)
    A function for doing a range search. The function takes as input two words. Given two
    words, the function should find all the words in between. The resulting words need not
    be sorted.
    */
    void range(const std::string & word1, const std::string & word2);

    std::size_t getSize();
};
#endif