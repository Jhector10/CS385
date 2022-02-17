/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Joshua Hector
 * Date        : February 13th, 2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (size_t i = 0; i < s.size(); i++) {
        if (isupper(s[i])) {
            return false;
        } if (isdigit(s[i])) {
            return false;
        }
    }

    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

    unsigned int vector = 0;
    unsigned int setter;
    unsigned int result;

    for (size_t i = 0; i < s.size(); i++) {
        setter = 1 << (s[i] - 'a'); // use the letter and compare it to the letter 'a' (as if 'a' is 0)
        result = setter & vector; // use the bitwise operator & (AND) to check the result with the vector
        if (result == setter || result != 0) { // if result is = to setter or non-zero, the letter has been seen before
            return false;
        } else { // if the result is 0, the letter hasn't been seen before
            vector = vector | setter; // set the vector equal to the bitwise operater | (OR) of setter and vector
        }
    }

    return true;

}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if(argc != 2) {
        // user gave the wrong number of command line arguments
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    } 
    
    if (!(is_all_lowercase(argv[1]))) { 
        // if a letter is not lowercase, it prints error message
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    } 
    
    else {
        // goes into the condition to check to see if the letters are all unique
        if(all_unique_letters(argv[1])) {
            cout << "All letters are unique." << endl;
        } else {
            cout << "Duplicate letters found." << endl;
        }
    }
}
