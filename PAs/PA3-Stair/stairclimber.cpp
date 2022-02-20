/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Joshua Hector
 * Date        : February 20, 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    vector<vector<int> > ways;
    vector<vector<int> > path;

    if (num_stairs < 1) { // if num_stairs is 0, send empty array and return the array
        ways.push_back(vector<int>());
    } else {
        for (int i = 1; i < 4; i++) { // iterate for the 1, 2, or 3 stairs at a time
            if (num_stairs >= i) {
                path = get_ways(num_stairs - i); // recursively 
                for (size_t j = 0; j < path.size(); j++) {
                    path[j].insert(path[j].begin(), i);
                }
                ways.insert(ways.end(), path.begin(), path.end());
            }
        }
    }

    return ways;
}

int num_digits(size_t num) {
    // Helper from Sieve hw: write code to determine how many digits are in an integer
    // This can help with displaying for display_ways
    int digits = 0;

    while(num != 0) {
        num /= 10;
        digits += 1;
    }

    return digits;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    size_t width = ways.size();
    int digits = num_digits(width);
    // determine how many spaces is needed for the list

    for(size_t i = 0; i < ways.size(); i++) { // iterate through each way to go up stairs
        cout << setw(digits) << (i + 1) << ". ["; // set the space needed before displaying
        for (size_t j = 0; j < ways[i].size(); j++) { // iterate through the way of getting up the stairs
            if (j == ways[i].size() - 1) { 
                // if you are at the end of the list, print the number with the "]", and go to next line
                cout << ways[i][j] << "]" << endl;;
            } else { // if you are not done, continue printing numbers
                cout << ways[i][j] << ", ";
            }
        }
    }
    
}

int main(int argc, char * const argv[]) {

    int numberOfStairs;
    vector< vector<int> > ways;

    if(argc != 2) {
        // user gave the wrong number of command line arguments
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    } 

    // Use stringstream for conversion
    istringstream iss(argv[1]);

    // Check for error.
    if ( !(iss >> numberOfStairs) || numberOfStairs < 1 ) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    ways = get_ways(numberOfStairs);

    if (numberOfStairs == 1) { // check the inside of the vector to see if it's only one stair
        cout << "1 way to climb 1 stair." << endl;
    } else { // prints out a starter sentence stating it's multiple stairs
    	cout << ways.size() << " ways to climb " << numberOfStairs << " stairs." << endl;
    }

    display_ways(ways);
    return 0;

}
