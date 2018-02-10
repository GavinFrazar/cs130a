#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <experimental\filesystem>
#include <sstream>

#include "BST.h"
#include "HashTable.h"


void promptMenu();

namespace fs = std::experimental::filesystem; //potentially needs to be changed on UNIX systems to std::filesystem
using namespace std;
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    using std::regex;
    using std::ifstream;
    using std::list;

    string stopwords[127] = { "i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now" };

    HashTable stopword_table(127);
    for (unsigned int i = 0; i < 127; ++i)
        stopword_table.insert(stopwords[i]);

    std::string path("hotels");
    string word;
    BST bst;

    //regex to parse data with
    regex rgx("[a-z'_-]+");
    for (auto& p : fs::recursive_directory_iterator(path))
    {
        if (fs::is_regular_file(p))
        {
            cout << p.path() << endl;
            ifstream input_file;
            input_file.open(p.path(), std::ios::binary);
            while (input_file >> word)
            {
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                if (!stopword_table.search(word) && std::regex_match(word, rgx))
                    bst.insert(word);
            }
        }
    }
    cout << bst.unique_word_count << endl;
    
    //loop forever
    while (true)
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