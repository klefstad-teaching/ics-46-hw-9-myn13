#include "ladder.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void error(string word1, string word2, string msg) {
    std::cerr << word1 << " and " << word2 << msg;
}


int min_of_three(int a, int b, int c){
    int min = (a >= b) ? b : a; 
    if ( min > c)
        min = c;
    return min;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d) {
/*given two strings with same length, calculate the total cost to transform string 1 to string 2
    delete letter first then add new letter at the same slot
    d: maximum distance we can use, return true if we can use < d steps
    else return false */
    int l1 = str1.length();
    int l2 = str2.length();

    if ( std::abs(l1 - l2) > d){
        return false;
    }

    if (str1 == str2)
        return true;

    vector<vector<int>> table(l1 + 1, vector<int>(l2 + 1, 0));

    for (int r = 0; r <= l1; ++r)
        table[r][0] = r;
    for (int c = 0; c < l2; ++c)
        table[0][c] = c;

    for (int r = 1; r <= l1; ++r){
        for (int c = 1; c <= l2; ++c){
            //if two characters are the same, set to the previous square in diagonal
            if (str1[r - 1] == str2[c - 1]){
                table[r][c] = table[r - 1][c - 1];
            }
            else
                table[r][c] = min_of_three( table[r-1][c-1], table[r][c - 1], table[r-1][c] ) + 1 ;

            // if (r==c && table[r][c] <= d) {
            //     return true;
            // }
            // std::cout << table[r][c];
        }
        // std::cout << endl;
    }
    // std::cout << table[l1][l2] << std::endl;
    return table[l1][l2] <= d;
    // return false;
}

bool is_adjacent(const string &word1, const string &word2){
    // return edit_distance_within(word1, word2, 1 );
    // return false;
    if (word1 == word2)
        return true;

    if (std::abs((int)word1.size() - (int) word2.size()) > 1) {
        return false;
    }
    
    if (word1.size() == word2.size()){
        int diff_count = 0;
        for (size_t i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i]) {
                diff_count++;
                if (diff_count > 1) {
                    return false;
                }
            }
        }
        return diff_count == 1;
    }

    if (std::abs((int)word1.size() - (int) word2.size()) == 1){
        const string&shorter =  (word1.size() < word2.size()) ? word1 : word2;
        const std::string& longer = (word1.size() < word2.size()) ? word2 : word1;

        size_t i = 0, j = 0;
        size_t diff_count = 0;
        while (i < shorter.size() && j < longer.size()) {
            if (shorter[i] != longer[j]) {
                diff_count++;
                if (diff_count > 1) {
                    return false;
                }
                j++; // Advance the longer string's index
            } else {
                i++;
                j++;
            }
        }
        return true;
    }
    return false;
}

template<typename Container>
bool findWord(const Container& list, const string & word){
    for (const auto& w : list){
        if (w == word)
            return true;
    }
    return false;
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list){
    if (begin_word == end_word)
        return {};

    string begin_lower = begin_word;
    string end_lower = end_word;
    transform(begin_lower.begin(), begin_lower.end(), begin_lower.begin(), ::tolower);
    transform(end_lower.begin(), end_lower.end(), end_lower.begin(), ::tolower);

    std::queue<vector<string>> ladder_queue; //store sequence of words
    ladder_queue.push({begin_word});

    std::unordered_set<string> visited;
    visited.insert(begin_lower);

    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        string last_word_lower = last_word;
        transform(last_word_lower.begin(), last_word_lower.end(), last_word_lower.begin(), ::tolower);
    
        if (last_word == end_word)
            return ladder;

        for (const string& word : word_list){
            if (is_adjacent(last_word_lower, word))
                if (!findWord(visited,word) ) {
                    if (visited.find(word) == visited.end()) {
                        visited.insert(word);
                        std::vector<std::string> new_ladder = ladder;
                        new_ladder.push_back(word);
                        ladder_queue.push(new_ladder);
                    }
                }
        }
    }
    return {};
}

void load_words(set<string> &word_list, const string &file_name){
    ifstream in(file_name);
    if (!in){
        throw runtime_error("Cannot open input file");
    }
    string word;
    while( in >> word){
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string> &ladder){
    if (ladder.empty())
        std::cout << "No word ladder found.\n";
    else{
        std::cout << "Word ladder found: ";
        for (string word : ladder){
            std::cout << word << " ";
        }
    std::cout << endl;
    }
}

#define my_assert(e) cout << #e << ((e) ? " passed" : " failed") << endl;
    
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}