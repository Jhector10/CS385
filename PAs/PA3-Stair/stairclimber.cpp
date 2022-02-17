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

    if (num_stairs <= 0) {
        ways.push_back(vector<int>());
    }
    
    for (int i = 1; i < 4; i++) {
        if (num_stairs >= i) {
            path = get_ways(num_stairs - 1);
            for (int j = 0; j < int(ways.size()); j++) {
                path[j].insert(path[j].begin(), i);
            }
            for (int n = 0; n < int(ways.size()); n++) {
                ways.push_back(path[n]);
            }
        }
    }

    return ways;

}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
}

int main(int argc, char * const argv[]) {

}
