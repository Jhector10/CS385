/*******************************************************************************
 * Filename: sieve.cpp
 * Author  : Joshua Hector
 * Version : 1.0
 * Date    : February 3rd, 2022
 * Description : Computes to find prime numbers using the Sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    // runs the sieve algorithm 
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_),
        primes_per_row = 80 / (max_prime_width + 1);

    int counter = 0; // counter to check the number of primes per row

    // if the amount of primes is less than the max primes_per_row
    if (num_primes() <= primes_per_row) {
        for (int i = 2; i <= limit_; i++) { // start from 2 
            if (is_prime_[i] && i != max_prime_) { // print out number if primes AND isn't max prime
                cout << i << " ";
            } else if (i == max_prime_) { // print out the last number
                cout << i << endl;
                break;
            }
        }
    } else { // if the amount of primes is greater than the number of primes per row
        for (int i = 2; i <= limit_; i++) { // start with 2 again
            if (i == max_prime_) { // if i is at the last one, print it and break the loop
                cout << setw(max_prime_width) << i;
                cout << endl;
                break;
            } else if (is_prime_[i]) {
                if (counter == primes_per_row) { // keep track of the primes that are in every row
                    cout << endl;
                    counter = 0; // reset counter with each new line
                } 
                cout << setw(max_prime_width) << i;
                counter++; // increment the amount of primes in the row at the end of each loop

                if (counter != primes_per_row) { // if it doesn't equal the last line, print a space
                    cout << " ";
                }
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int count = 0;
    for(int i = 0; i <= limit_; i++) {
        if (is_prime_[i]) {
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {

    // sets the first two numbers, 0 and 1 to false (not prime)
    is_prime_[0] = false; 
    is_prime_[1] = false;

    // fills in the entire array with all the numbers as true
    for (int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
    }

    // write sieve algorithm from the psuedocode provided
    for (int i = 2; i <= sqrt(limit_); i++) { 
        if (is_prime_[i]) {
            for(int j = i*i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }

    // places the number of primes in the is_prime_ array into num_primes_
    num_primes_ = count_num_primes();

    // after running the sieve algorithm, finds the max prime of the array
    for(int i = limit_; i >= 2; i--) {
        if (is_prime_[i]) {
            max_prime_ = i;
            break;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits = 0;

    while(num != 0) {
        num /= 10;
        digits += 1;
    }

    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve numbers(limit);
    cout << endl;
    cout << "Number of primes found: " << numbers.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    numbers.display_primes();

    return 0;
}
