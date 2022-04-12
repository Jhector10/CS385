/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Joshua Hector
 * Version     : 1.0
 * Date        : March 27th, 2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    
    long inversions = 0;
    for (int i = 0; i < length; i++) {
        for (int j = i+1; j < length; j++) {
            if (array[i] > array[j]) {
                inversions++;
            }
        }
    }

    return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
    long inversions = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {

    int mid;
    int mid2;
    int copyLow;
    long inversions = 0;

    if (low < high) {
        mid = low + (high - low) / 2;
        inversions = mergesort(array, scratch, low, mid);
        inversions += mergesort(array, scratch, mid+1, high);

        mid2 = mid + 1;
        copyLow = low;

        for (int i = low; i <= high; i++) {
            if (copyLow <= mid && (mid2 > high || array[copyLow] <= array[mid2])) {
                scratch[i] = array[copyLow];
                copyLow++;
            } else {
                scratch[i] = array[mid2];
                mid2++;
                inversions += (mid - copyLow) + 1;
            }
        }

        for (int i = low; i <= high; i++) {
            array[i] = scratch[i];
        }
    }
    
    return inversions;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    if (argc > 2) {
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    } else if (argc == 2) {
        istringstream isc(argv[1]);
        string input;
        if (!(isc >> input) || input != "slow") {
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return 1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    long inversions = 0;
    int length = values.size();

    if (length == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    if (argc == 2) {
        inversions = count_inversions_slow(&values[0], length);
        cout << "Number of inversions: " << inversions << endl;
    } else {
        inversions = count_inversions_fast(&values[0], length);
        cout << "Number of inversions: " << inversions << endl;
    }

    return 0;
}
