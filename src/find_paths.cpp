#include <iostream>
#include "directed_graph.hpp"

using namespace std;

void find_paths_from_vertex(DirectedGraph graph, string vertex, vector<string>& path, int targetLength) {
    if (path.size() == targetLength) {
        if (path.front() != path.back()) {
            for (string vertex : path) {
                cout << vertex << " ";
            }
            cout << endl;
        }
        return;
    }

    int offset = -1;
    while (graph.get_next_index(vertex, offset) != -1) {
        offset += 1;
        string nextVertex = graph.get_vertex(vertex, offset);
        path.push_back(nextVertex);
        find_paths_from_vertex(graph, nextVertex, path, targetLength);
        path.pop_back();
    }
}

void find_paths(vector<vector<int>> weights_matrix, vector<string> alphabet) {
    DirectedGraph graph;

    for (int i = 0; i < weights_matrix.size(); ++i) {
        graph.add_v(alphabet[i], "Not visited");
    }
    for (int i = 0; i < weights_matrix.size(); ++i) {
        for (int j = 0; j < weights_matrix[i].size(); ++j) {
            if (weights_matrix[i][j] > 0) {
                graph.add_e(alphabet[i], alphabet[j], weights_matrix[i][j]);
            }
        }
    }
    graph.print_graph();

    int x, n = 6;
    cout << "Enter the path length x: ";
    cin >> x;

    cout << "All non-cyclic paths of length " << x << ":" << endl;
    for (int vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
        vector<string> path = {alphabet[vertexIndex]};
        find_paths_from_vertex(graph, alphabet[vertexIndex], path, x);
    }
}
