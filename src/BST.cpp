#include "BST.h"

void BST::deleteTree(Node * root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void BST::range(Node * root, const std::string & word1, const std::string & word2)
{
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

void BST::sort(Node * root, std::vector<std::string>& sorted_v)
{
    if (root == nullptr)
        return;
    sort(root->left, sorted_v);
    sorted_v.push_back(root->word);
    sort(root->right, sorted_v);
}

void BST::deepCopy(Node *& first,Node * const & second)
{
    if (second == nullptr)
        return;

    first = new Node(second->word);
    first->count = second->count;
    deepCopy(first->left, second->left);
    deepCopy(first->right, second->right);
}

BST::BST()
{
    this->root_ = nullptr;
    this->size_ = 0;
}

BST::BST(const BST & rhs)
    :   BST()
{
    deepCopy(this->root_, rhs.root_);
    this->size_ = rhs.size_;
}

BST::BST(BST && rhs)
    : BST()
{
    swap(*this, rhs);
}

BST & BST::operator=(BST rhs)
{
    swap(*this, rhs);
    return *this;
}

BST::~BST()
{
    this->deleteTree(this->root_);
    this->size_ = 0;
}

bool BST::search(const std::string & word)
{
    Node* target = root_;
    while (target != nullptr)
    {
        int compare = word.compare(target->word);
        if (compare == 0)
            return true;
        else if (compare < 0)
            target = target->left;
        else
            target = target->right;
    }
    return false;
}

void BST::insert(const std::string& word)
{
    if (this->root_ == nullptr)
    {
        this->root_ = new Node(word);
        ++this->size_;
        return;
    }

    Node* target = this->root_;
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
                ++this->size_;
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
                ++this->size_;
                return;
            }
        }
    }
}

void BST::delete_word(const std::string & word)
{
    Node* target = this->root_;
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
                if (target == this->root_)
                    branch_to_target = &(this->root_);
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
                --this->size_;
                return;
            }
        }
    }
}

std::vector<std::string> BST::sort()
{
    std::vector<std::string> sorted_v;
    sorted_v.reserve(this->size_);
    this->sort(this->root_, sorted_v);
    return sorted_v;
}

void BST::range(const std::string & word1, const std::string & word2)
{
    range(this->root_, word1, word2);
}

std::size_t BST::getSize()
{
    return this->size_;
}

void swap(BST & first, BST & second)
{
    using std::swap; //ADL
    swap(first.root_, second.root_);
    swap(first.size_, second.size_);
}
