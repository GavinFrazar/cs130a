#include "BST.h"

void BST::delete_tree(Node * root)
{
    if (root == nullptr)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

Node * BST::search_tree(std::string word)
{
    Node* target = this->root;
    while (target != nullptr)
    {
        if (target->word == word)
            break;
        else if (word < target->word)
            target = target->left;
        else if (word > target->word)
            target = target->right;
    }
    return target;
}

void BST::to_lower(std::string & s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void BST::range(Node * root, std::string word1, std::string word2)
{
    to_lower(word1);
    to_lower(word2);

    if (root == nullptr)
        return;

    if (root->word < word1)
    {
        range(root->right, word1, word2);
    }
    else if (root->word > word2)
    {
        range(root->left, word1, word2);
    }
    else
    {
        range(root->left, word1, word2);
        std::cout << root->word << std::endl;
        range(root->right, word1, word2);
    }
}

void BST::sort(Node * root)
{
    if (root == nullptr)
        return;
    sort(root->left);
    std::cout << root->word << std::endl;
    sort(root->right);
}

BST::BST()
{
    this->root = nullptr;
}

BST::~BST()
{
    this->delete_tree(this->root);
}

bool BST::search_word(std::string word)
{
    to_lower(word);
    Node* result = search_tree(word);
    if (result != nullptr)
        return true;
    else
        return false;
}

void BST::insert_word(std::string word)
{
    to_lower(word);
    if (this->root == nullptr)
    {
        this->root = new Node(word);
        return;
    }

    Node* target = this->root;
    while (target != nullptr)
    {
        if (word == target->word)
        {
            ++target->counter;
            return;
        }
        else if (word < target->word)
        {
            if (target->left != nullptr)
                target = target->left;
            else
            {
                Node* tmp = new Node(word);
                target->left = tmp;
                return;
            }
        }
        else if (word > target->word)
        {
            if (target->right != nullptr)
                target = target->right;
            else
            {
                Node* tmp = new Node(word);
                target->right = tmp;
                return;
            }
        }
    }    
}

void BST::delete_word(std::string word)
{
    Node* target = this->root;
    while (target != nullptr)
    {
        if (target->word == word)
        {
            if (target->counter == 1)
            {
                //replace deleted node with left-most node
                Node* replacement;
                if (target->right != nullptr)
                {
                    replacement = target->right;
                    while (replacement->left != nullptr)
                    {
                        replacement = replacement->left;
                    }
                    //TODO---delete and replace

                }
            }
            else
                --target->counter;
        }
    }
}

void BST::sort()
{
    sort(this->root);
}

void BST::range(std::string word1, std::string word2)
{
    range(this->root, word1, word2);
}