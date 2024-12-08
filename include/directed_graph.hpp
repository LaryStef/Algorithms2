#pragma once
#include <vector>

using namespace std;

class DirectedGraph {
private:
    struct Vertex {
        string name;
        string mark;
    };

    vector<Vertex> vertices;
    vector<vector<int>> incidenceMatrix;
    int findVertexIndex(string name);

public:
    void add_v(string name, string mark);
    void add_e(string v, string w, int c);
    void del_v(string name);
    void del_e(string v, string w);
    void edit_v(string name, string newMark);
    void edit_e(string v, string w, int newC);
    int get_first_index(string name);
    int get_next_index(string name, int offset);
    string get_vertex(string name, int i);
    void print_graph();
};
