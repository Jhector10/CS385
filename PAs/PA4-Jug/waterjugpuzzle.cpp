/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : James Fong and Joshua Hector
 * Date        : March 6th, 2022
 * Description : Solve the famous water jug puzzle using breadth-first search
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// Struct to represent state of water in the jugs.
struct State
{
    int a, b, c;
    string directions;

    State(int _a, int _b, int _c) : a{_a}, b{_b}, c{_c} {}

    int getA()
    {
        return a;
    }

    int getB()
    {
        return b;
    }

    int getC()
    {
        return c;
    }

    // String representation of state in tuple form.
    string to_string()
    {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

vector<vector<State> > tree;
queue<State> bfsQueue;

void fill(int A, int B)
{
    // creates a tree that extends out to fill with the max capacity of the jugs
    State temp(-1, -1, -1);

    for (int i = 0; i < A + 1; i++)
    {
        vector<State> temp1;
        tree.push_back(temp1);
        for (int j = 0; j <= B; j++)
        {
            tree[i].push_back(temp);
        }
    }
}

bool is_equal(State &current, State &goal)
{
    // used to compare if the goal state has been reached
    if ((current.getA() == goal.getA()) && (current.getB() == goal.getB()) && (current.getC() == goal.getC()))
    {
        return true;
    }
    return false;
}

void pourWater(State &current, int from, int to, int staysSame, const int cap, string &direction)
{
    int available = cap - to;
    // checks the current water jug to see if he can hold the amount of water needed
    State temp(-1, -1, -1);

    if (available > 0 && from > 0)
    {
        // checks if the transfer is valid
        for (int i = available; i > 0 && from > 0; i--)
        {
            // does the transition from jug to jug based on capacity
            to++;
            from--;
        }

        // C to A
        if (direction.compare("C to A") == 0)
        {
            // C++ has compare to compare strings, = 0 if equal
            State transfer(to, staysSame, from); // transfer C to A
            if (is_equal(tree[transfer.a][transfer.b], temp))
            {
                // if state has not been seen, add to the queue
                bfsQueue.push(transfer);
                tree[transfer.a][transfer.b] = current;
            }
        }
        // B to A
        if (direction.compare("B to A") == 0)
        {
            State transfer(to, from, staysSame);
            if (is_equal(tree[transfer.a][transfer.b], temp))
            {
                bfsQueue.push(transfer);
                tree[transfer.a][transfer.b] = current;
            }
        }
        // C to B
        if (direction.compare("C to B") == 0)
        {
            State transfer(staysSame, to, from);
            if (is_equal(tree[transfer.a][transfer.b], temp))
            {
                bfsQueue.push(transfer);
                tree[transfer.a][transfer.b] = current;
            }
        }
        // A to B
        if (direction.compare("A to B") == 0)
        {
            State transfer(from, to, staysSame);
            if (is_equal(tree[transfer.a][transfer.b], temp))
            {
                bfsQueue.push(transfer);
                tree[transfer.a][transfer.b] = current;
            }
        }
        // B to C
        if (direction.compare("B to C") == 0)
        {
            State transfer(staysSame, from, to);
            if (is_equal(tree[transfer.a][transfer.b], temp))
            {
                bfsQueue.push(transfer);
                tree[transfer.a][transfer.b] = current;
            }
        }
        // A to C
        if (direction.compare("A to C") == 0)
        {
            State transfer(from, staysSame, to);
            if (is_equal(tree[transfer.a][transfer.b], temp))
            {
                bfsQueue.push(transfer);
                tree[transfer.a][transfer.b] = current;
            }
        }
    }
}

void findPath(State &goalState)
{
    string pathway = "";
    vector<string> path;
    State currentState = tree[goalState.a][goalState.b];

    if (!(goalState.a == 0 && goalState.b == 0))
    {
        if (goalState.a != currentState.a)
        { 
            if (goalState.b != currentState.b)
            { // // if the jug A and jug B were changed 
                if (currentState.a < goalState.a)
                { // if the gallon was transferred from B to A (current is less than the goal), then we poured from A
                    if (abs(goalState.b - currentState.b) == 1)
                    {
                        pathway = "Pour " + to_string(abs(goalState.b - currentState.b)) + " gallon from B to A. " + goalState.to_string();
                    }
                    else
                    {
                        pathway = "Pour " + to_string(abs(goalState.b - currentState.b)) + " gallons from B to A. " + goalState.to_string();
                    }
                    path.push_back(pathway);
                }
                else
                { // else means the previous state was greater than the goal A, so A was poured into
                    if (abs(goalState.a - currentState.a) == 1)
                    {
                        pathway = "Pour " + to_string(abs(goalState.a - currentState.a)) + " gallon from A to B. " + goalState.to_string();
                    }
                    else
                    {
                        pathway = "Pour " + to_string(abs(goalState.a - currentState.a)) + " gallons from A to B. " + goalState.to_string();
                    }
                    path.push_back(pathway);
                }
                findPath(tree[goalState.a][goalState.b]);
            }
            else 
            { // this else conducts the same pattern but from A and C (as in B stays the same)
                if (currentState.a < goalState.a)
                {
                    if (abs(goalState.c - currentState.c) == 1)
                    {
                        pathway = "Pour " + to_string(abs(goalState.c - currentState.c)) + " gallon from C to A. " + goalState.to_string();
                    }
                    else
                    {
                        pathway = "Pour " + to_string(abs(goalState.c - currentState.c)) + " gallons from C to A. " + goalState.to_string();
                    }
                    path.push_back(pathway);
                }
                else 
                { // if A from the previous is greater, then A was poured into from C
                    if (abs(goalState.a - currentState.a) == 1)
                    {
                        pathway = "Pour " + to_string(abs(goalState.a - currentState.a)) + " gallon from A to C. " + goalState.to_string();
                    }
                    else
                    {
                        pathway = "Pour " + to_string(abs(goalState.a - currentState.a)) + " gallons from A to C. " + goalState.to_string();
                    }
                    path.push_back(pathway);
                }
                findPath(tree[goalState.a][goalState.b]);
            }
        }
        else if (goalState.b != currentState.b) 
        { // this else conducts the same pattern but from C and B (as in A stays the same)
            if (currentState.b < goalState.b)
            {
                if (abs(goalState.b - currentState.b) == 1)
                {
                    pathway = "Pour " + to_string(abs(goalState.b - currentState.b)) + " gallon from C to B. " + goalState.to_string();
                }
                else
                {
                    pathway = "Pour " + to_string(abs(goalState.c - currentState.c)) + " gallons from C to B. " + goalState.to_string();
                }
                path.push_back(pathway);
            }
            else
            {
                if (abs(goalState.c - currentState.c) == 1)
                {
                    pathway = "Pour " + to_string(abs(goalState.c - currentState.c)) + " gallon from B to C. " + goalState.to_string();
                }
                else
                {
                    pathway = "Pour " + to_string(abs(goalState.c - currentState.c)) + " gallons from B to C. " + goalState.to_string();
                }
                path.push_back(pathway);
            }
            findPath(tree[goalState.a][goalState.b]);
        }
    }

    if (goalState.a == 0 && goalState.b == 0) 
    { // if A and B are empty, this means we are at the initial state 
        cout << "Initial state. " << goalState.to_string() << endl;
    }

    for (uint i = 0; i < path.size(); i++)
    {
        cout << path[i] << endl;
    }
}

void bfs(const int capacityA, const int capacityB, const int capacityC, int goalA, int goalB, int goalC)
{
    State current(0, 0, capacityC);
    State goal(goalA, goalB, goalC);
    // initialize the input given from the user
    bool solution = true;
    fill(capacityA, capacityB);
    State temp(0, 0, 0);
    string direction = "";
    tree[current.a][current.b] = temp;
    bfsQueue.push(current);

    while (!(is_equal(bfsQueue.front(), goal)))
    {
        // utilize the is_equal function to continue the while loop
        if (bfsQueue.empty())
        {
            cout << "No solution." << endl;
            solution = false;
            break;
        }
        current = bfsQueue.front();
        bfsQueue.pop();

        // transfer water FROM C TO A, as B STAYS THE SAME, CAP is on A
        direction = "C to A";
        pourWater(current, current.c, current.a, current.b, capacityA, direction);

        // transfer water FROM B TO A, as C STAYS THE SAME, CAP is on A
        direction = "B to A";
        pourWater(current, current.b, current.a, current.c, capacityA, direction);

        // transfer water FROM C TO B, as A STAYS THE SAME, CAP is on B
        direction = "C to B";
        pourWater(current, current.c, current.b, current.a, capacityB, direction);

        // transfer water FROM A TO B, as C STAYS THE SAME, CAP is on B
        direction = "A to B";
        pourWater(current, current.a, current.b, current.c, capacityB, direction);

        // transfer water FROM B TO C, as A STAYS THE SAME, CAP is on C
        direction = "B to C";
        pourWater(current, current.b, current.c, current.a, capacityC, direction);

        // transfer water FROM A TO C, as B STAYS THE SAME, CAP is on C
        direction = "A to C";
        pourWater(current, current.a, current.c, current.b, capacityC, direction);
    }

    if (solution)
    {
        findPath(bfsQueue.front());
    }
}

bool errorHandling(char *argv[])
{
    int gallon;

    for (int i = 1; i < 7; i++)
    {
        istringstream iss(argv[i]);
        if (!(iss >> gallon) || gallon < 0 || (gallon == 0 && i == 3))
        {
            // checks to see if capacity of c is 0 or if any jugs are < 0
            if (i == 1)
            {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
            }
            if (i == 2)
            {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
            }
            if (i == 3)
            {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
            }
            if (i == 4)
            {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug A." << endl;
            }
            if (i == 5)
            {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug B." << endl;
            }
            if (i == 6)
            {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug C." << endl;
            }
            return false;
        }
    }

    int i = 1;
    int j = 4;

    while (i <= 3)
    {
        // checks to see that all of the goals are less than the capacity's of the jugs
        int capacity, goal;
        istringstream iss_cap(argv[i]);
        iss_cap >> capacity;
        istringstream iss_goal(argv[j]);
        iss_goal >> goal;
        if (goal > capacity)
        {
            if (i == 1)
            {
                cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
            }
            if (i == 2)
            {
                cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
            }
            if (i == 3)
            {
                cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
            }
            return false;
        }
        i++;
        j++;
    }

    int sumOfJugs = 0, jugC;
    istringstream iss(argv[3]);
    iss >> jugC;
    for (int i = 4; i < 7; i++)
    {
        // this takes the sum of the gallons at the end of the main code
        int temp;
        istringstream iss_sum(argv[i]);
        iss_sum >> temp;
        sumOfJugs += temp;
    }
    if (sumOfJugs != jugC)
    {
        // if the sum of the gallons does not equal the beginning of jug C, error
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{

    if (argc != 7)
    {
        // user gave the wrong number of command line arguments
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    if (!errorHandling(argv))
    {
        return 1;
    }

    bfs(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

    return 0;
}