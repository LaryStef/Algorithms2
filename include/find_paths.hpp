#pragma once
#include "directed_graph.hpp"

using namespace std;

void find_paths(vector<vector<int>> weights_matrix, vector<string> alphabet);
void find_paths_from_vertex(DirectedGraph graph, string vertex, vector<string>& path, int targetLength);
