#include <iostream>
#include <string>

#include "BST.h"


int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

//simple text-based user interface
    string option_search    = "[1] Search for a word.";
    string option_insert    = "[2] Inseart a word.";
    string option_delete    = "[3] Delete a word with.";
    string option_sort      = "[4] Sort the binary search tree.";
    string option_range     = "[5] Search for words that lie within a range.";
    string main_menu =  "\n" + option_search + "\n"
                        + option_insert + "\n"
                        + option_delete + "\n"
                        + option_sort + "\n"
                        + option_range + "\n";
    
    string prompt_search    = "Enter a word to be searched for:\n\t";
    string prompt_insert    = "Enter a word to be inserted:\n\t";
    string prompt_delete    = "Enter a word to be deleted (or decremented):\n\t";
    string prompt_sort      = "Sorting...";
    string prompt_range1    = "Enter the first word:\n\t";
    string prompt_range2    = "Enter the second word:\n\t";

    BST bst;
    bst.insert_word("m");
    bst.insert_word("f");
    bst.insert_word("s");
    bst.insert_word("a");
    bst.insert_word("g");
    bst.insert_word("q");
    bst.insert_word("r");
    bst.insert_word("z");
    bst.insert_word("b");
    bst.insert_word("w");
    bst.insert_word("y");
    
    auto &words = bst.range("a", "g");
    for (auto &word : words)
        cout << word << endl;
    words = bst.range("a", "g");
    for (auto &word : words)
        cout << word << endl;

//loop forever
    while(true)
    {
        cout << main_menu << endl;
        unsigned short option_select;
        cin >> option_select;
        cout << endl;
        if (option_select == 1)
        {
            string word;
            cout << prompt_search << endl;
            cin >> word;
        }else if (option_select == 2)
        {
            string word;
            cout << prompt_insert << endl;
            cin >> word;
        }else if (option_select == 3)
        {
            string word;
            cout << prompt_delete << endl;
            cin >> word;
        }else if (option_select == 4)
        {
            cout << prompt_sort << endl;
        }else if (option_select == 5)
        {
            string word1, word2;
            cout << prompt_range1 << endl;
            cin >> word1;
            cout << "\n" + prompt_range2 << endl;
            cin >> word2;
        }else
        {
            cout << "Selection invalid. Please enter a valid number [1, 5]" << endl;
        }
    }
    return 0;
}