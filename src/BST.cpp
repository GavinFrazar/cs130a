#include "BST.h"

void BST::delete_tree(Node * root)
{
    if (root == nullptr)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

Node * BST::find_node(std::string word)
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
    this->unique_word_count = 0;
}

BST::~BST()
{
    this->delete_tree(this->root);
    this->unique_word_count = 0;
}

bool BST::search_word(std::string word)
{
    to_lower(word);
    Node* result = find_node(word);
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
            ++target->count;
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
                ++this->unique_word_count;
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
                ++this->unique_word_count;
                return;
            }
        }
    }
}

void BST::delete_word(std::string word)
{
    Node* target = this->root;
    Node** branch_to_target = nullptr;
    while (target != nullptr)
    {
        if (target->word < word)
        {
            branch_to_target = &(target->right);
            target = target->right;
        }
        else if (target->word > word)
        {
            branch_to_target = &(target->left);
            target = target->left;
        }
        else //target->word == word
        {
            if (target->count > 1)
            {
                --target->count;
                return;
            }
            else
            {
                if (target == this->root)
                    branch_to_target = &(this->root);
                if (target->left != nullptr && target->right != nullptr)  //two children
                {
                    //find minimum in right subtree
                    Node* min = target->right;
                    Node** branch_to_min = nullptr;
                    while (min->left != nullptr)
                    {
                        branch_to_min = &(min->left);
                        min = min->left;
                    }

                    if (branch_to_min != nullptr)
                        *branch_to_min = min->right;

                    min->left = target->left;
                    if (target->right->word != min->word)
                        min->right = target->right;
                    else
                        min->right = nullptr;

                    if (branch_to_target != nullptr)
                        *branch_to_target = min;
                }
                else if (target->right != nullptr)  //only a right child
                {
                    if (branch_to_target != nullptr)
                        *branch_to_target = target->right;
                }
                else if (target->left != nullptr)  //only a left child
                {
                    if (branch_to_target != nullptr)
                        *branch_to_target = target->left;
                }
                else  //no children
                {
                    if (branch_to_target != nullptr)
                        *branch_to_target = nullptr;
                }
                delete target;
                --this->unique_word_count;
                return;
            }
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