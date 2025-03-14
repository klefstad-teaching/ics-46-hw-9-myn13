#include "dijkstras.h"

int main(){
    string filename = "medium.txt";
    Graph G;
    file_to_graph(filename, G);
    int destination = 4;

    vector<int> previous(G.numVertices, -1); 
    //declaration vector in C: vector<int> vec(numbers of elements, all initialized to)
    cout << "Dijkstra shortest path from 0: \n";
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    vector<int> path = extract_shortest_path(distances, previous, destination);

    if(!path.empty()){
        int total_cost = distances[destination];
        print_path(path, total_cost);
    }
    else {
        cout << "No path exists from source to " << destination << endl;
    }
    return 0;
}