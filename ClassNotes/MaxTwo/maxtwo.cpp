/*******************************************************************************
 * Filename: maxtwo.cpp
 * Author  : Joshua Hector
 * Version : 1.0
 * Date    : January 21, 2022
 * Description : Computes the max of two numbers on the command line
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

/*
int max(int n, int m) {
    if(n > m) {
        return n;
    } else {
        return m;
    } 
    return n > m ? n : m; 
    // ternary operator, if n > m -> return n, if not return m
}
*/

int main (int argc, char* argv[]) {
    // argc is the number of command line arguments (../maxtwo 27 53 = 3)
    // argv is an array (argv[0] = ../maxtwo, argv[1] = String(27), argv[2] = String(53))

    float n, m;
    istringstream iss; // input string stream

    if(argc != 3) {
        // user gave the wrong number of command line arguments
        cerr << "Usage: " << argv[0] << " <integer n> <integer m>" << endl;
        return 1; // 1 means that something went wrong in the program

        // cout means a print message out for the user
        // cerr means an error message out for the user (takes priority)
    }

    // change the string into an integer
    
    iss.str(argv[1]); // initialize iss to read from argv[1]
    if (!(iss >> n)) { // now we actually read it, and place it into n
        cerr << "first command line argument must an integer" << endl;
        return 1;
    }

    iss.clear(); // always reset before you read another stream

    iss.str(argv[2]); 
    if (!(iss >> m)) { 
        cerr << "second command line argument must an integer" << endl;
        return 1;
    }

    cout << "n is: " << n << endl;
    cout << "m is: " << m << endl;
    
    cout << "max(" << n << ", " << m << ") is: " << max(n, m) << endl;

    // compute square root 

    // nextGuess = (lastGuess + n / lastGuess) / 2

    return 0;
}