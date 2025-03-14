#include "ladder.h"

void test_circular_ladder() {
    set<string> word_list = {"cat", "cot", "cog", "dog", "dot"};
    
    cout << "Testing circular ladder prevention:" << endl;
    cout << "Word list: ";
    for (const auto& word : word_list) {
        cout << word << " ";
    }
    cout << endl;

    // Test case 1: Potential circular ladder
    string start = "cat";
    string end = "dog";
    cout << "\nTest 1: " << start << " to " << end << endl;
    vector<string> ladder = generate_word_ladder(start, end, word_list);
    
    if (ladder.empty()) {
        cout << "No ladder found (as expected for this small word list)." << endl;
    } else {
        cout << "Ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
        
        // Check for circular pattern
        set<string> unique_words(ladder.begin(), ladder.end());
        if (unique_words.size() == ladder.size()) {
            cout << "PASS: No circular pattern detected." << endl;
        } else {
            cout << "FAIL: Circular pattern detected!" << endl;
        }
    }

    // Test case 2: Valid short ladder
    start = "cat";
    end = "cot";
    cout << "\nTest 2: " << start << " to " << end << endl;
    ladder = generate_word_ladder(start, end, word_list);
    
    if (ladder.empty()) {
        cout << "FAIL: No ladder found, but a valid ladder exists." << endl;
    } else {
        cout << "Ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
        
        if (ladder.size() == 2) {
            cout << "PASS: Correct shortest ladder found." << endl;
        } else {
            cout << "FAIL: Ladder is longer than expected." << endl;
        }
    }
}

int main()
{
    // Test case for error function
    // cout << "Testing error function:" << endl;
    // error("cat", "dog", "Words are not adjacent");
    // cout << endl;

    // // Test cases for edit_distance_within function
    // cout << "Testing edit_distance_within function:" << endl;
    // cout << "cat and dog within 3 edits: " << (edit_distance_within("cat", "dog", 3) ? "true" : "false") << endl;
    // cout <<  "apple and zoom within 1 edit" << (edit_distance_within("apple", "zoom",1) ? "true" : "false") << endl;
    // cout << "cat and car within 1 edit: " << (edit_distance_within("cat", "car", 1) ? "true" : "false") << endl;
    // cout << endl;

    // // Test cases for is_adjacent function
    // cout << "Testing is_adjacent function:" << endl;
    // cout << "cat and cot: " << (is_adjacent("cat", "cot") ? "adjacent" : "not adjacent") << endl;
    // cout << "dog and log: " << (is_adjacent("dog", "log") ? "adjacent" : "not adjacent") << endl;
    // cout << endl;

    // Test case for load_words function
    // set<string> word_list;
    // cout << "Testing load_words function:" << endl;
    // load_words(word_list, "words.txt");
    // cout << "Number of words loaded: " << word_list.size() << endl;
    // cout << endl;

    // Test case for generate_word_ladder function
    // cout << "Testing generate_word_ladder function:" << endl;
    // set<string> arr = {"poon", "plee", "same", 
    //                 "poie", "plie", "poin", "plea"};
    // string start = "poon";
    // string target = "plea";
    // vector<string> ladder = generate_word_ladder(start, target, arr);
    // print_word_ladder(ladder);

    // cout << "Testing generate_word_ladder function:" << endl;
    // set<string> arr1 = {"were"};
    // string start1 = "were";
    // string target1 = "were";
    // vector<string> ladder1 = generate_word_ladder(start1, target1, arr1);
    // print_word_ladder(ladder1);
    // cout << ladder1.size();
 
    // vector<string> ladder = generate_word_ladder("cap", "bat", word_list);
    // cout << "Word ladder from 'cap' to 'bat:" << endl;
    // print_word_ladder(ladder);
    // cout << endl;

    // Test case for generate_word_ladder function
    // cout << "Testing generate_word_ladder function:" << endl;
    // set<string> arr = {"cat", "bat", "bog", 
    //                 "bag", "cot"};
    // string start = "cat";
    // string target = "bag";
    // vector<string> ladder = generate_word_ladder(start, target, arr);
    // print_word_ladder(ladder);

    // // Test verify_word_ladder function
    // cout << "Testing verify_word_ladder function:" << endl;
    // verify_word_ladder();
    // cout << endl;
    
    test_circular_ladder();
    return 0;
}