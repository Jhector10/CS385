#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "Hello world!" << endl;
    cout << fixed; // print the output in a particular format
    cout << setprecision(20); // set the amount of places in the decimal output
    cout << 3.0 / 73472372.0 << endl;
    return 0;
}