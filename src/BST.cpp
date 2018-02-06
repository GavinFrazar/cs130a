#include "BST.h"

void BST::delete_tree(Node *& root)
{
    using std::vector;
    vector<Node*> targets;
    targets.push_back(root);
    for (auto &target : targets)
    {
        if (target->left != nullptr)
            targets.push_back(target->left);
        if (target->right != nullptr)
            targets.push_back(target->right);
        delete target;
    }
}

Node * BST::search_tree(const std::string& word)
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

BST::BST()
{
    this->root = nullptr;
}

BST::~BST()
{
    this->delete_tree(this->root);
}

bool BST::search_word(const std::string& word)
{
    Node* result = search_tree(word);
    if (result != nullptr)
        return true;
    else
        return false;
}

void BST::insert_word(const std::string &word)
{
    Node* target = this->root;
    while (target != nullptr)
    {
        if (word == target->word)
        {
            ++target->counter;
            return;
        }
        else if (word < target->word)
            target = target->left;
        else if (word > target->word)
            target = target->right;
    }
    target = new Node(word);
}

void BST::delete_word(std::string word)
{
    Node* target = this->root;
    while (target != nullptr)
    {
        if (target->word == word)
        {
            if (target->counter == 0)
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

void BST::sort_tree()
{
}

std::vector<std::string&> BST::range(std::string word1, std::string word2)
{
    Node* min = this->root;
    std::vector<Node*> targets;
    while (min != nullptr)
    {
        if (word1 == min->word)
        {

        }
        else if (word1 < min->word)
        {
            targets.push_back(min);
            min = min->left;
        }
    }
    
    std::vector<std::string&> words;
    for (auto &target : targets)
    {
        if (target->left != nullptr)
            targets.push_back(target->left);
        if (target->right != nullptr)
            targets.push_back(target->right);
        words.push_back(target->word);
    }
    return words;
}