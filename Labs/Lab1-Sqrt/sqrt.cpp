/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Joshua Hector
 * Version : 1.0
 * Date    : January 27, 2022
 * Description : Computes the square root of a number
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

double sqrt(double num, double epsilon) {

    double last_guess = 1;
    double next_guess = (last_guess + num / last_guess) / 2;

    if (num < 0) {
        return numeric_limits<double>::quiet_NaN();
    }

    if (num == 0 || num == 1) {
        return num == 0 ? 0 : 1;
    }

    while (abs(last_guess - next_guess) >= epsilon) {
        last_guess = next_guess;
        next_guess = (last_guess + num / last_guess) / 2;
    }

    return next_guess;
}

int main (int argc, char* argv[]) {
    // argc is the number of command line arguments (../maxtwo 27 53 = 3)
    // argv is an array (argv[0] = ../maxtwo, argv[1] = String(27), argv[2] = String(53))

    double n, m;
    istringstream iss; // input string stream

    cout << fixed;
    cout << setprecision(8);

    if(argc < 2 || argc > 3) {
        // user gave the wrong number of command line arguments
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    } else {
        // if there is no epsilon argument
        iss.str(argv[1]); // initialize iss to read from argv[1]
        if (!(iss >> n)) { // now we actually read it, and place it into n
            cerr << "Error: Value argument must be a double." << endl;
            return 1;
        } 

        if (argc == 2) {
            cout << sqrt(n, 0.0000001) << endl;
        }

        iss.clear(); 
        if (argc == 3) {
            iss.str(argv[2]);
            if (!(iss >> m) || m <= 0) {
                cerr << "Error: Epsilon argument must be a positive double." << endl;
                return 1;
            }
            cout << sqrt(n, m) << endl;
        }  
    }     
}