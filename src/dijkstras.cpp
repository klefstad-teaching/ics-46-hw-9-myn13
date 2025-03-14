#include "dijkstras.h"
#include <queue>
#include <random>
#include <variant>

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous){
    vector<bool> visited(G.size(), false);
    //initialize all distances to a huge integer
    vector<int> distances(G.size(), INF);
    //distance of the source to source && previous vertex is unknown
    distances[source] = 0;
    previous[source] = -1;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap; //minHeap use to handle the smallest path
    minHeap.push({0, source}); //make a pair between source and distance
    /* from the source to destination distance
                            source      0
                            B           huge integer
                            c           huge integer... */

    while (!minHeap.empty()){
        int u = minHeap.top().second;
        int dist_u = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) 
            continue;
        visited[u]= true;
        if (dist_u > distances[u])
            continue;
        for (const Edge& e: G[u]){
            int v = e.dst;
            int weight = e.weight;

            if (!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int> & distances, const vector<int> &previous, int destination){
    vector<int> temp; //print all verticies get through to reach destination
    /*having lists of shortest distances, now we can use previous to keep track the previous vertices
    then reverse it to get the shortest path from the source to destination*/

    if (destination < 0 || destination >= (int) distances.size()){
        cerr << "Error: Destination vertex does not exist" << endl;
        return temp;
    }

    if (distances[destination] == INF) {
        return temp;  // Return empty path if no path exists
    }

    for (int i = destination; i > -1; i = previous[i]) {
        temp.push_back(i);
    }

    int first = 0;
    int last = temp.size() - 1;
    while (first < last){
        std::swap(temp[first], temp[last]);
        first++;
        last--;
    }

    vector<int> path;
    for (int i: temp){
        path.push_back(i);
    }

    return path;
}

void print_path(const vector<int> & v, int total){
    if (!v.empty())
    {
        /*taking a list of vertices v and their total cost, print the path and the total cost*/
        for (size_t i = 0; i < v.size(); ++i) 
            cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}

