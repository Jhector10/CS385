/*******************************************************************************
 * Filename: student.cpp
 * Author  : Joshua Hector
 * Version : 1.0
 * Date    : January 29, 2022
 * Description : Student class that returns a vector of failing students
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class Student {

public:
	// Constructor that uses an initializer list.
	Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} { }

	// Methods that do not modify member variables should be declared const.
	void print_info() const {
		cout << full_name() << ", GPA: " << fixed
			 << setprecision(2) << gpa() << ", ID: " << id() << endl;
	}

	// Accessor (getter), declared const.
	string full_name() const {
		return first_ + " " + last_;
	}

    float gpa() const {
        return gpa_;
    }

    int id() const {
        return id_;
    }

private:
	// Member variables (fields). Use the trailing _ for these variables.
	string first_, last_;
    float gpa_;
    int id_;
}; // semicolon is required!

/**
    * Takes a vector of Student objects, and returns a new vector
    * with all Students whose GPA is < 1.0.
    */
    vector<Student> find_failing_students(const vector<Student> &students) {
        vector<Student> failing_students;
        // Iterates through the students vector, appending each student whose gpa is
        // less than 1.0 to the failing_students vector.
        for(size_t i = 0; i < students.size(); i++) {
            if (students[i].gpa() < 1.0) {
                failing_students.push_back(students[i]);
            }
        }
        return failing_students;
    }

    /**
    * Takes a vector of Student objects and prints them to the screen.
    */
    void print_students(const vector<Student> &students) {
    // Iterates through the students vector, calling print_info() for each student.
        for(size_t i = 0; i < students.size(); i++) {
            students[i].print_info();
        }
    }

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen. */
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;

    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl;
    cout << "Failing students:";

    if (find_failing_students(students).empty()) {
        cout << " None" << endl;
    } else {
        cout << endl; 
        print_students(find_failing_students(students));
    }

    return 0;
}