#include "BST.h"

void BST::delete_tree(Node * root)
{
    using std::list;
    list<Node*> targets;
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
    Node* result = search_tree(word);
    if (result != nullptr)
        return true;
    else
        return false;
}

void BST::insert_word(std::string word)
{
    if (this->root == nullptr)
    {
        this->root = new Node(word);
        return;
    }

    Node* target = this->root;
    while (target != nullptr)
    {
        Node* parent = target;
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

void BST::sort_tree()
{
}

std::list<std::string> BST::range(std::string word1, std::string word2)
{
    std::list<std::string> words;
    std::list<Node*> targets;

    Node* subtree_root = this->root;
    while (subtree_root != nullptr)
    {
        if (subtree_root->word < word1)
        {
            subtree_root = subtree_root->right;
        }
        else if (subtree_root->word > word2)
        {
            subtree_root = subtree_root->left;
        }
        else //word1 <= subtree_root->word <= word2
        {
            words.push_back(subtree_root->word);
            Node* floor = subtree_root->left;
            Node* ceiling = subtree_root->right;

            while (floor != nullptr)
            {
                if (floor->word >= word1)
                {
                    words.push_back(floor->word);
                    Node* target = floor->right;
                    targets.push_back(target);
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
                    Node* target = ceiling->left;
                    targets.push_back(target);
                    ceiling = ceiling->right;
                }
                else
                {
                    ceiling = ceiling->left;
                }
            }
            break;
        }
    }
    
    for (auto &target : targets)
    {
        if (target == nullptr)
            continue;
        if (target->left != nullptr)
            targets.push_back(target->left);
        if (target->right != nullptr)
            targets.push_back(target->right);
        words.push_back(target->word);
    }
    return words;
}