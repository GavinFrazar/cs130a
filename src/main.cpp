#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>

#include "BST.h"
#include "HashTable.h"

void promptMenu();

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    using std::regex;
    using std::ifstream;
    using std::list;

    HashTable ht(15);
    ht.insert("a");
    ht.insert("k");
    ht.insert("g");
    ht.insert("h");
    ht.insert("c");
    ht.insert("i");
    ht.insert("j");
    ht.insert("d");
    ht.insert("b");
    ht.insert("e");
    ht.insert("f");

    if (ht.search("a"))
        cout << "found it!" << endl;

    ht.delete_word("i");
    ht.search("i");

    //regex to parse dataset with
     regex rgx("[A-z'-]+");

    ifstream input_file;
    //open each file, parse and add to BST and HashTable

    string seq = "SoMe-capitals some words... more words. ah! whomst've'd in-n-out burger this_iS_whom'st've'd! ";

    for (std::sregex_iterator it(seq.begin(), seq.end(), rgx), it_end; it != it_end; ++it)
        cout << (*it)[0] << "\n";

//loop forever
    while(true)
    {
        promptMenu();
    }
    return 0;
}

void promptMenu()
{
    using std::string;
    using std::cout;
    using std::cin;
    using std::endl;
    string option_search = "[1] Search for a word.";
    string option_insert = "[2] Inseart a word.";
    string option_delete = "[3] Delete a word with.";
    string option_sort = "[4] Sort the binary search tree.";
    string option_range = "[5] Search for words that lie within a range.";
    string main_menu = "\n" + option_search + "\n"
        + option_insert + "\n"
        + option_delete + "\n"
        + option_sort + "\n"
        + option_range + "\n";

    string prompt_search = "Enter a word to be searched for:\n\t";
    string prompt_insert = "Enter a word to be inserted:\n\t";
    string prompt_delete = "Enter a word to be deleted (or decremented):\n\t";
    string prompt_sort = "Sorting...";
    string prompt_range1 = "Enter the first word:\n\t";
    string prompt_range2 = "Enter the second word:\n\t";

    cout << main_menu << endl;
    unsigned short option_select;
    cin >> option_select;
    cout << endl;
    if (option_select == 1)
    {
        string word;
        cout << prompt_search << endl;
        cin >> word;
    }
    else if (option_select == 2)
    {
        string word;
        cout << prompt_insert << endl;
        cin >> word;
    }
    else if (option_select == 3)
    {
        string word;
        cout << prompt_delete << endl;
        cin >> word;
    }
    else if (option_select == 4)
    {
        cout << prompt_sort << endl;
    }
    else if (option_select == 5)
    {
        string word1, word2;
        cout << prompt_range1 << endl;
        cin >> word1;
        cout << "\n" + prompt_range2 << endl;
        cin >> word2;
    }
    else
    {
        cout << "Selection invalid. Please enter a valid number [1, 5]" << endl;
    }
}