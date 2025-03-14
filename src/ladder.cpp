#include "ladder.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
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
    return table[l1][l2] <= d ? true : false;
    // return false;
}

bool is_adjacent(const string &word1, const string &word2){
    return edit_distance_within(word1, word2, 1 );
    // return false;
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

    std::set<string> visited;
    visited.insert(begin_lower);

    while (!ladder_queue.empty()){
        std::vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        if (last_word == end_word) 
            return ladder;
        
        for (const string& word : word_list){
            string word_lower = word;
            transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);
            if (is_adjacent(last_word, word_lower)){
                if (find(ladder.begin(), ladder.end(), word_lower) != ladder.end()) {
                        continue;  // Skip this word to avoid a circular ladder
                    }
                if (visited.find(word_lower) == visited.end() ) {
                    visited.insert(word_lower);
                    std::vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word_lower == end_word)
                        return new_ladder;
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