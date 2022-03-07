/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : James Fong and Josh Hector
 * Date        : March 2th, 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Struct to represent state of water in the jugs.
struct State
{
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

    // String representation of state in tuple form.
    string to_string()
    {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

// State capacity(0,0,0);

/*void bfs(const int CapacityA, const int CapacityB, int CapacityC, int GoalA, int GoalB, int GoalC)
{

}
*/

void display_steps(State *s)
{
    if (s->parent != nullptr)
    {
        display_steps(s->parent);
    }
    cout << s->directions << s->to_string() << endl;
}

bool is_Goal_Met(State &current, State &goal)
{
    if (&current->a == GoalA && current->b == GoalB && current->c == GoalC)
        {
            isSolvable = true;
            display_steps(current);
            break;
        }
}

void bfs(const int CapacityA, const int CapacityB, int CapacityC, int GoalA, int GoalB, int GoalC)
{
    // 2D array that keeps track of parents.
    bool **visited = new bool *[CapacityA + 1];
    for (int i = 0; i < CapacityA + 1; i++)
    {
        visited[i] = new bool[CapacityB + 1];
        fill(visited[i], visited[i] + (CapacityB + 1), false);
    }

    // Queue that keeps track of the states.
    queue<State *> q;

    // Initalize initial state
    State *s = new State(0, 0, CapacityC, "Initial state. ");

    // Store initial state on queue
    q.push(s);

    // Boolean that checks if the puzzle is solvable with the given inputs.
    bool isSolvable = false;
    int pour;
    int available_space;

    while (!q.empty())
    {
        State *current = q.front();
        q.pop();

        if (current->a == GoalA && current->b == GoalB && current->c == GoalC)
        {
            isSolvable = true;
            display_steps(current);
            break;
        }

        // Check if state has already been visited
        if (visited[current->a][current->b] == true)
        {
            continue;
        }

        visited[current->a][current->b] = true;

        // 1. Pour C into A
        if (current->c != 0)
        {
            available_space = (CapacityA - current->a);
            if (current->c > available_space)
            {
                pour = available_space;
            }
            else
            {
                pour = current->c;
            }
            if (pour != 0 && pour != 1)
            {
                q.push(new State(pour + current->a, current->b, current->c - pour, "Pour " + to_string(pour) + " gallons from C to A. "));
                q.back()->parent = current;
            }
            else if (pour != 0 && pour == 1)
            {
                q.push(new State(pour + current->a, current->b, current->c - pour, "Pour " + to_string(pour) + " gallon from C to A. "));
                q.back()->parent = current;
            }
        }

        // 2. Pour B into A
        if (current->b != 0)
        {
            available_space = (CapacityA - current->a);
            if (current->b > available_space)
            {
                pour = available_space;
            }
            else
            {
                pour = current->b;
            }
            if (pour != 0 && pour != 1)
            {
                q.push(new State(pour + current->a, current->b - pour, current->c, "Pour " + to_string(pour) + " gallons from B to A. "));
                q.back()->parent = current;
            }
            else if (pour != 0 && pour == 1)
            {
                q.push(new State(pour + current->a, current->b - pour, current->c, "Pour " + to_string(pour) + " gallon from B to A. "));
                q.back()->parent = current;
            }
        }

        // 3. Pour C into B
        if (current->c != 0)
        {
            available_space = (CapacityB - current->b);
            if (current->c > available_space)
            {
                pour = available_space;
            }
            else
            {
                pour = current->c;
            }
            if (pour != 0 && pour != 1)
            {
                q.push(new State(current->a, current->b + pour, current->c - pour, "Pour " + to_string(pour) + " gallons from C to B. "));
                q.back()->parent = current;
            }
            else if (pour != 0 && pour == 1)
            {
                q.push(new State(current->a, current->b + pour, current->c - pour, "Pour " + to_string(pour) + " gallon from C to B. "));
                q.back()->parent = current;
            }
        }

        // 4. Pour A into B
        if (current->a != 0)
        {
            available_space = (CapacityB - current->b);
            if (current->a > available_space)
            {
                pour = available_space;
            }
            else
            {
                pour = current->a;
            }
            if (pour != 0 && pour != 1)
            {
                q.push(new State{current->a - pour, current->b + pour, current->c, "Pour " + to_string(pour) + " gallons from A to B. "});
                q.back()->parent = current;
            }
            else if (pour != 0 && pour == 1)
            {
                q.push(new State{current->a - pour, current->b + pour, current->c, "Pour " + to_string(pour) + " gallon from A to B. "});
                q.back()->parent = current;
            }
        }

        // 5. Pour B into C
        if (current -> b != 0)
        {
            available_space = (CapacityC - current -> c);
            if (current -> b > available_space)
            {
                pour = available_space;
            }
            else
            {
                pour = current -> b;
            }
            if (pour != 0 && pour != 1)
            {
                q.push(new State{current->a, current->b - pour, current->c + pour, "Pour " + to_string(pour) + " gallons from B to C. "});
                q.back()->parent = current;
            }
            else if (pour != 0 && pour == 1)
            {
                q.push(new State{current->a, current->b - pour, current->c + pour, "Pour " + to_string(pour) + " gallon from B to C. "});
                q.back()->parent = current;
            }
        }

        // 6. Pour A into C
        if (current -> a != 0)
        {
            available_space = (CapacityC - current -> c);
            if (current -> a > available_space)
            {
                pour = available_space;
            }
            else
            {
                pour = current->a;
            }
            if (pour != 0 && pour != 1)
            {
                q.push(new State{current->a - pour, current->b, current->c + pour, "Pour " + to_string(pour) + " gallons from A to C. "});
                q.back()->parent = current;
            }
            else if (pour != 0 && pour == 1)
            {
                q.push(new State{current->a - pour, current->b, current->c + pour, "Pour " + to_string(pour) + " gallon from A to C. "});
                q.back()->parent = current;
            }
        }
    }

    if (isSolvable == false)
    {
        cout << "No solution." << endl;
    }

    // Deleting the array 'visited'
    for (int i = 0; i < CapacityA + 1; i++)
    {
        delete[] visited[i];
    }
    delete[] visited;
    delete s;

}

bool errorHandling(char *const argv[]) {
    int gallon;

    for (int i = 1; i < 7; i++) {
        istringstream iss(argv[i]);
        if (!(iss >> gallon) || gallon < 0 || (gallon == 0 && i == 3)) { 
            // checks to see if capacity of c is 0 or if any jugs are < 0
            if (i == 1) {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug A." << endl;
            } if (i == 2) {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug B." << endl;
            } if (i == 3) {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C." << endl;
            } if (i == 4) {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug A." << endl;
            } if (i == 5) {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug B." << endl;
            } if (i == 6) {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug C." << endl;
            }
            return false;
        }
    }

    int i = 1;
    int j = 4;

    while (i <= 3) {
        // checks to see that all of the goals are less than the capacity's of the jugs
        int capacity, goal;
        istringstream iss_cap(argv[i]);
        iss_cap >> capacity;
        istringstream iss_goal(argv[j]);
        iss_goal >> goal;
        if(goal > capacity) {
            if (i == 1) {
                cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
            } if (i == 2) {
                cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
            } if (i == 3) {
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
    for (int i = 4; i < 7; i++) {
        // this takes the sum of the gallons at the end of the main code
        int temp;
        istringstream iss_sum(argv[i]);
        iss_sum >> temp;
        sumOfJugs += temp;
    } if (sumOfJugs != jugC) {
        // if the sum of the gallons does not equal the beginning of jug C, error
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return false;
    }

    return true;
}

int main(int argc, char *const argv[])
{
    // checks if there are sufficient arguments
    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    //int argument;
    //istringstream iss;

    //char jug[3] = {'A', 'B', 'C'};
    //vector<int> input;
    /*
    // checks if the input argument is an available argument.
    for (int i = 1; i < argc; i++)
    {
        iss.str(argv[i]);

        if (i < 4)
        {
            if (!(iss >> argument) || argument < 1)
            {
                cerr << "Error: Invalid capacity \'" << argv[i] << "\' for jug " << jug[i - 1] << "." << endl;
                return 1;
            }
        }

        else if (!(iss >> argument) || argument < 0)
        {
            cerr << "Error: Invalid goal \'" << argv[i] << "\' for jug " << jug[i % 4] << "." << endl;
            return 1;
        }
        input.push_back(argument);
        iss.clear();
    }

    for (int i = 1; i <= argc; i++)
    {
        if (i <= 3)
        {
            if (atoi(argv[i + 3]) > atoi(argv[i]))
            {
                cerr << "Error: Goal cannot exceed capacity of jug " << jug[i - 1] << "." << endl;
                return 1;
            }
        }
    }

    if (atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6]) != atoi(argv[3]))
    {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 1;
    }
    */

    if(!errorHandling(argv))
    {
        return 1;
    }

    bfs(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    return 0;
    // bfs(input[0],input[1], input[2], input[3], input[4],input[5]);
}
