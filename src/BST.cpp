#include "BST.h"

void BST::delete_tree(Node * root)
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

std::vector<std::string> BST::range(std::string word1, std::string word2)
{

    std::vector<std::string> words;
    Node* target = this->root;
    std::vector<Node*> targets;
    while (target != nullptr)
    {
        if (target->word < word1)
        {
            target = target->right;
        }
        else if (target->word > word2)
        {
            target = target->left;
        }
        else //word1 <= target->word <= word2
        {
            Node* floor = target->left;
            Node* ceiling = target->right;

            while (floor != nullptr)
            {
                if (floor->word >= word1)
                {
                    words.push_back(floor->word);
                    //then push all the words in floor->right subtree
                    floor = floor->left;
                }
                else
                {
                    floor = floor->right;
                }
            }

            while (ceiling != nullptr)
            {
                if (ceiling->word <= word2)
                {
                    words.push_back(ceiling->word);
                    //then push all words in ceiling->left subtree
                    ceiling = ceiling->right;
                }
                else
                {
                    ceiling = ceiling->left;
                }
            }
        }
    }
    
    return words;
}