#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <experimental/filesystem>
#include <chrono>
#include <limits>
#include <sstream>
#include <vector>

#include "BST.h"
#include "HashTable.h"

namespace fs = std::experimental::filesystem; //potentially needs to be changed on UNIX systems to std::filesystem

void to_lower(std::string & s);

const double NANOS_PER_SECOND = 1000000000.0;

int main()
{
    std::string stopwords[127] = { "i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now" };

    HashTable stopword_table(127);
    for (unsigned int i = 0; i < 127; ++i)
        stopword_table.insert(stopwords[i]);

    std::string path("hotels-small");
    std::vector<std::string> words;

    BST bst;
    //regex to parse data with
    std::regex rgx("[a-z]+[a-z_'-]*");

    for (auto& p : fs::recursive_directory_iterator(path))
    {
        if (fs::is_regular_file(p))
        {
            std::ifstream input_file;
            input_file.open(p.path());

            std::string token;
            while (input_file >> token)
            {
                to_lower(token);
                for (std::sregex_iterator it(token.begin(), token.end(),rgx), it_end; it != it_end; ++it)
                {
                    std::string word = it->str();
                    if (!stopword_table.search(word))
                        words.push_back(word);
                }
            }
        }
    }

    HashTable ht((unsigned long long)(words.size()*1.5));

    for (std::vector<std::string>::iterator it = words.begin(), it_end = words.end(); it != it_end; ++it)
    {
        bst.insert(*it);
        ht.insert(*it);
    }



    std::cout << std::boolalpha;
    std::cout.precision(17);
    //loop forever
    while (true)
    {
        unsigned short option_select;
        std::cin >> option_select;
        while (std::cin.fail())
        {
            std::cout << "Invalid selection. Enter a valid option [1, 5]:\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            std::cin >> option_select;
        }
        if (option_select == 1)  //search option selected
        {
            std::string word;
            std::cin >> word;

            //time bst search
            auto start_bst = std::chrono::high_resolution_clock::now();
            std::cout << bst.search(word) << std::endl;
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable search
            auto start_ht = std::chrono::high_resolution_clock::now();
            std::cout << ht.search(word) << std::endl;
            auto end_ht = std::chrono::high_resolution_clock::now();
            auto dur_ht = end_ht - start_ht;
            auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            std::cout << "Hash: " << std::fixed << ns_ht / NANOS_PER_SECOND << std::endl;
        }
        else if (option_select == 2)  //insert option selected
        {
            std::string word;
            std::cin >> word;

            //time bst insert
            auto start_bst = std::chrono::high_resolution_clock::now();
            bst.insert(word);
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable insert
            auto start_ht = std::chrono::high_resolution_clock::now();
            ht.insert(word);
            auto end_ht = std::chrono::high_resolution_clock::now();
            auto dur_ht = end_ht - start_ht;
            auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            std::cout << "Hash: " << std::fixed << ns_ht / NANOS_PER_SECOND << std::endl;
        }
        else if (option_select == 3)  //delete option selected
        {
            std::string word;
            std::cin >> word;

            //time bst delete
            auto start_bst = std::chrono::high_resolution_clock::now();
            bst.delete_word(word);
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable delete
            auto start_ht = std::chrono::high_resolution_clock::now();
            ht.delete_word(word);
            auto end_ht = std::chrono::high_resolution_clock::now();
            auto dur_ht = end_ht - start_ht;
            auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            std::cout << "Hash: " << std::fixed << ns_ht / NANOS_PER_SECOND << std::endl;
        }
        else if (option_select == 4)  //sort option selected
        {
            const std::string base_path = "/cs130a-01/build/";
            const std::string sort_output_file = "sort_output.txt";
            std::ofstream out(sort_output_file);

            //time bst insert
            auto start_bst = std::chrono::high_resolution_clock::now();
            std::vector<std::string>& bst_sorted = bst.sort();
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();
            for (auto& word : bst_sorted)
                out << word << "\n";

            //time hashtable insert
            auto start_ht = std::chrono::high_resolution_clock::now();
            std::vector < std::string>& ht_sorted = ht.sort();
            auto end_ht = std::chrono::high_resolution_clock::now();
            auto dur_ht = end_ht - start_ht;
            auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();
            for (auto& word : ht_sorted)
                out << "\n" << word;

            out.close();
            std::cout << base_path << sort_output_file << std::endl;
            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            std::cout << "Hash: " << std::fixed << ns_ht / NANOS_PER_SECOND << std::endl;
        }
        else if (option_select == 5)
        {
            std::string word1, word2;
            std::cin >> word1;
            std::cin >> word2;

            //time bst insert
            auto start_bst = std::chrono::high_resolution_clock::now();
            bst.range(word1, word2);
            auto end_bst = std::chrono::high_resolution_clock::now();
            auto dur_bst = end_bst - start_bst;
            auto ns_bst = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_bst).count();

            //time hashtable insert
            auto start_ht = std::chrono::high_resolution_clock::now();
            ht.range(word1, word2);
            auto end_ht = std::chrono::high_resolution_clock::now();
            auto dur_ht = end_ht - start_ht;
            auto ns_ht = std::chrono::duration_cast<std::chrono::nanoseconds>(dur_ht).count();

            std::cout << "BST: " << std::fixed << ns_bst / NANOS_PER_SECOND << std::endl;
            std::cout << "Hash: " << std::fixed << ns_ht / NANOS_PER_SECOND << std::endl;
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