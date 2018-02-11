#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <experimental/filesystem>
#include <chrono>
#include <limits>

#include "BST.h"
#include "HashTable.h"

namespace fs = std::experimental::filesystem; //potentially needs to be changed on UNIX systems to std::filesystem

void to_lower(std::string & s);

#define NANOS_PER_SECOND 1000000000.0

int main()
{
    std::string stopwords[127] = { "i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now" };

    HashTable stopword_table(127);
    for (unsigned int i = 0; i < 127; ++i)
        stopword_table.insert(stopwords[i]);

    std::string path("hotels");
    std::string word;
    BST bst;

    //regex to parse data with
    std::regex rgx("[a-z]+[a-z'_-]*");
    unsigned long long count = 0;
    for (auto& p : fs::recursive_directory_iterator(path))
    {
        if (fs::is_regular_file(p))
        {
            std::cout << p.path() << std::endl;
            std::ifstream input_file;
            input_file.open(p.path(), std::ios::binary);
            while (input_file >> word)
            {
                to_lower(word);
                if (!stopword_table.search(word) && std::regex_match(word, rgx))
                {
                    ++count;
                    bst.insert(word);
                }
            }
        }
    }
    std::cout << "unique: " << bst.unique_word_count << std::endl;
    std::cout << "total: " << count << std::endl;

    std::string option_search = "[1] Search for a word.";
    std::string option_insert = "[2] Inseart a word.";
    std::string option_delete = "[3] Delete a word with.";
    std::string option_sort = "[4] Sort the binary search tree.";
    std::string option_range = "[5] Search for words that lie within a range.";
    std::string main_menu = "\n" + option_search + "\n"
        + option_insert + "\n"
        + option_delete + "\n"
        + option_sort + "\n"
        + option_range + "\n";

    std::string prompt_search = "Enter a word to be searched for:\n\t";
    std::string prompt_insert = "Enter a word to be inserted:\n\t";
    std::string prompt_delete = "Enter a word to be deleted (or decremented):\n\t";
    std::string prompt_sort = "Sorting...";
    std::string prompt_range1 = "Enter the first word:\n\t";
    std::string prompt_range2 = "Enter the second word:\n\t";

    std::cout << std::boolalpha;
    std::cout.precision(17);

    //loop forever
    while (true)
    {
        std::cout << main_menu << std::endl;
        unsigned short option_select;
        std::cin >> option_select;
        std::cout << std::endl;
        if (option_select == 1)
        {
            std::string word;
            std::cout << prompt_search << std::endl;
            std::cin >> word;

            //time bst search
            auto start_bst = std::chrono::high_resolution_clock::now();
            std::cout << bst.search(word) << std::endl;
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable search
            //auto start_ht = std::chrono::high_resolution_clock::now();
            //cout << ht.search(word) << endl;
            //auto end_ht = std::chrono::high_resolution_clock::now();
            //auto dur_ht = end_ht - start_ht;
            //auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            //cout << "Hash: " << fixed <<ns_ht / NANOS_PER_SECOND << endl;
        }
        else if (option_select == 2)
        {
            std::string word;
            std::cout << prompt_insert << std::endl;
            std::cin >> word;

            //time bst insert
            auto start_bst = std::chrono::high_resolution_clock::now();
            bst.insert(word);
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable insert
            //auto start_ht = std::chrono::high_resolution_clock::now();
            //ht.insert(word);
            //auto end_ht = std::chrono::high_resolution_clock::now();
            //auto dur_ht = end_ht - start_ht;
            //auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            //cout << "Hash: " << fixed <<ns_ht / NANOS_PER_SECOND << endl;
        }
        else if (option_select == 3)
        {
            std::string word;
            std::cout << prompt_delete << std::endl;
            std::cin >> word;

            //time bst delete
            auto start_bst = std::chrono::high_resolution_clock::now();
            bst.delete_word(word);
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable delete
            //auto start_ht = std::chrono::high_resolution_clock::now();
            //ht.delete_word(word);
            //auto end_ht = std::chrono::high_resolution_clock::now();
            //auto dur_ht = end_ht - start_ht;
            //auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            //cout << "Hash: " << fixed <<ns_ht / NANOS_PER_SECOND << endl;
        }
        else if (option_select == 4)
        {
            std::cout << prompt_sort << std::endl;
            std::string sortfile_path;
            std::cin >> sortfile_path;
            std::ofstream out(sortfile_path);

            //time bst insert
            auto start_bst = std::chrono::high_resolution_clock::now();
            std::string bst_sort = bst.sort();
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable insert
            //auto start_ht = std::chrono::high_resolution_clock::now();
            //string ht_sort = ht.sort();
            //auto end_ht = std::chrono::high_resolution_clock::now();
            //auto dur_ht = end_ht - start_ht;
            //auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            //string output = bst_sort + "\n" + ht_sort;
            //out << output;
            out << bst_sort;    //REMOVE ME PLEASE REMOVE ME AHHHHHHHHHHHHH
            out.close();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            //cout << "Hash: " << fixed <<ns_ht / NANOS_PER_SECOND << endl;
        }
        else if (option_select == 5)
        {
            std::string word1, word2;
            std::cout << prompt_range1 << std::endl;
            std::cin >> word1;
            std::cout << "\n" + prompt_range2 << std::endl;
            std::cin >> word2;

            //time bst insert
            auto start_bst = std::chrono::high_resolution_clock::now();
            bst.range(word1, word2);
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();
            
            //time hashtable insert
            //auto start_ht = std::chrono::high_resolution_clock::now();
            //ht.range(word1,word2);
            //auto end_ht = std::chrono::high_resolution_clock::now();
            //auto dur_ht = end_ht - start_ht;
            //auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            //cout << "Hash: " << fixed <<ns_ht / NANOS_PER_SECOND << endl;
        }
        else
        {
            std::cout << "Selection invalid. Enter a valid number [1, 5]" << std::endl;
        }
    }
    return 0;
}

void to_lower(std::string & s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}