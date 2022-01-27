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
	Student(string first_, string last_, float gpa_, int id_) : first{first_}, last{last_}, gpa{gpa_}, id(id_) { }

	// Methods that do not modify member variables should be declared const.
	void print_coords() const {
		cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed
			 << setprecision(2) << z_ << ")" << endl;
	}

    /**
    * Takes a vector of Student objects, and returns a new vector
    * with all Students whose GPA is < 1.0.
    */
    vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
    // Iterates through the students vector, appending each student whose gpa is
    // less than 1.0 to the failing_students vector.
    return failing_students;
    }

    /**
    * Takes a vector of Student objects and prints them to the screen.
    */
    void print_students(const vector<Student> &students) {
    // Iterates through the students vector, calling print_info() for each student.
    }

	// Mutator (setter).
	void set_x(int x) {
		x_ = x;
	}

	// Accessor (getter), declared const.
	int get_x() const {
		return x_;
	}

private:
	// Member variables (fields). Use the trailing _ for these variables.
	string first_, last_;
    int id_;
	float gpa_;
}; // semicolon is required!

// Pass by reference, and using an iterator (which is an object
// that can be used essentially as if it were a pointer):
void display_points(const vector<Student> &students) {
	for(auto it = points.cbegin(); it != points.cend(); it++) {
		it->print_coords(); // Same as: (*it).print_coords();
	}
}

void display_points_v2(const vector<MyPoint> &points) {
	for(size_t i = 0; i < points.size(); i++) {
		points[i].print_coords();
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
    cout << endl << "Failing students:";

    if (students.size() == 0) {
        cout << "None" << endl;
    } else {
        print_students(find_failing_students(students));
    }

    // TODO
    // Print a space and the word 'None' on the same line if no students are failing.
    // Otherwise, print each failing student on a separate line.
    return 0;
}