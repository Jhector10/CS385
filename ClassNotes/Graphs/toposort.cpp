#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

vector<int> toposort(vector<int> *graph, int V) {
    int *indegree = new int[V]; // array is dynamic, so use the 'new'

    fill(indegree, indegree + V, 0);
    // same as a for loop filling in the array with 0s

    for(int v1 = 0; v1 < V; v1++) {
        // to check each starting v1 going to the other vertex

        for(int v2 : graph[v1]) {
            // check each ending vertex and increase their count by 1
            indegree[v2]++;
        }

        // for(size_t i = 0; i < graph[v1].size(); i++) {
        //     int v2 = graph[v1][i];
        //     indegree[v2]++;
        // }
    }

    queue<int> S;

    for(int vertex = 0; vertex < V; vertex++) {
        if(indegree[vertex] == 0) {
            S.push(vertex); 
            // i.e if a vertex does not have a starting vertex 
            // then push that vertex into the queue
        }
    }

    vector<int> L;

    while(!S.empty()) {
        int vertex = S.front(); // take the first vertex from of the queue (does not delete)
        S.pop(); // then take it out of the queue

        L.push_back(vertex); // then add the vertex to the end of the list

        for(int adjacent : graph[vertex]) {
            indegree[adjacent]--;
            if (indegree[adjacent] == 0) {
                // TO DO: add the neighbors in increasing order
                S.push(adjacent);
            }
        }
    }

    // this means that there is a cycle somewhere, so what is in L is useless
    for(int vertex = 0; vertex < V; vertex++) {
        if(indegree[vertex] != 0) {
            L.clear();
            break;
        }
    }


    delete[] indegree;
    return L;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<int> *graph = new vector<int>[V];

    while(E--) {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        // go through each vector in the list and sort them
    }

    for(int i = 0; i < V; i++) {
        sort(graph[v1].begin(), graph[v1].end());
    }

    sort(graph[v1].begin(), graph[v1].end);

    vector<int> order = toposort(graph, V);

    if(order.size() > 0) {
        for(int vertex : order) {
            cout << vertex << " ";
        }
        cout << endl;
    } else {
        cout << "failed" << endl;
    }

    delete[] graph;
    return 0;

}