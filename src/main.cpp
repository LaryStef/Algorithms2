#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class DirectedGraph {
private:
    struct Vertex {
        string name;
        string mark;
    };

    vector<Vertex> vertices;
    vector<vector<int>> incidenceMatrix;

    int findVertexIndex(string name) {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i].name == name) {
                return i;
            }
        }
        throw invalid_argument("Vertex with given name does not exist.");
    }

public:
    void add_v(string name, string mark) {
        // Проверяем, существует ли вершина с таким именем
        for (Vertex vertex : vertices) {
            if (vertex.name == name) {
                cout << "Vertex with given name already exists." << endl;
                return;
            }
        }

        Vertex newVertex;
        newVertex.name = name;
        newVertex.mark = mark;
        vertices.push_back(newVertex);

        incidenceMatrix.push_back(vector<int>());
        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            incidenceMatrix[vertices.size()].push_back(0);
        }
    }

    void add_e(string v, string w, int c) {
        int from;
        int to;
        try {
            from = findVertexIndex(v);
            to = findVertexIndex(w);
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return;
        }

        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            if (incidenceMatrix[from][i] != 0 && incidenceMatrix[to][i] != 0) {
                cout << "Edge already exists." << endl;
                return;
            }
        }

        for (int i = 0; i < incidenceMatrix.size(); ++i) {
            if (i == from) {
                incidenceMatrix[i].push_back(c);
            }
            else if (i == to) {
                incidenceMatrix[i].push_back(-c);
            }
            else {
                incidenceMatrix[i].push_back(0);
            }
        }
    }

    void del_v(string name) {
        int index;
        try {
            index = findVertexIndex(name);
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return;
        }

        for (int incidence : incidenceMatrix[index]) {
            if (incidence != 0) {
                cout << "Vertex has incident edges." << endl;
                return;
            }
        }
        vertices.erase(vertices.begin() + index);
        incidenceMatrix.erase(incidenceMatrix.begin() + index);
    }

    void del_e(string v, string w) {
        int from;
        int to;
        try {
            from = findVertexIndex(v);
            to = findVertexIndex(w);
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return;
        }

        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            if (incidenceMatrix[from][i] != 0 && incidenceMatrix[to][i] != 0) {
                for (int j = 0; j < incidenceMatrix.size(); ++j) {
                    incidenceMatrix[j].erase(incidenceMatrix[j].begin() + i);
                }
            }
        }
    }

    void edit_v(string name, string newMark) {
        int index;
        try {
            index = findVertexIndex(name);
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return;
        }

        vertices[index].mark = newMark;
    }

    void edit_e(string v, string w, int newC) {
        int from;
        int to;
        try {
            from = findVertexIndex(v);
            to = findVertexIndex(w);
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return;
        }

        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            if (incidenceMatrix[from][i] != 0 && incidenceMatrix[to][i] != 0) {
                incidenceMatrix[from][i] = newC;
                incidenceMatrix[to][i] = -newC;
                return;
            }
        }
    }

    int get_first_index(string name) { return get_next_index(name, -1); }

    int get_next_index(string name, int index) {
        int vertexIndex;
        try {
            vertexIndex = findVertexIndex(name);
        }
        catch (invalid_argument e) {
            cout << e.what() << endl;
            return -1;
        }

        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            if (incidenceMatrix[vertexIndex][i] != 0) {
                if (index >= 0) {
                    index -= 1;
                    continue;
                }
                for (int j = 0; j < incidenceMatrix.size(); ++j) {
                    if (incidenceMatrix[j][i] != 0) {
                        return j;
                    }
                }
            }
        }
        return -1;
    }

    string get_vertex(string name, int i) { return vertices[get_next_index(name, i - 1)].name; }

    void print_graph() {
        cout << "Vertices:\n";
        for (Vertex vertex : vertices) {
            cout << vertex.name << " (" << vertex.mark << ")\n";
        }
        cout << "\nIncidence Matrix:\n";
        cout << "  ";
        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            cout << i << " ";
        }

        for (int i = 0; i < incidenceMatrix.size(); ++i) {
            cout << endl;
            cout << vertices[i].name << " ";
            for (int j = 0; j < incidenceMatrix[i].size(); ++j) {
                cout << incidenceMatrix[i][j] << " ";
            }
        }
        cout << endl << endl;
    }
};

int main() {
    DirectedGraph graph;

    graph.add_v("A", "Mark A");
    graph.add_v("B", "Mark B");
    graph.add_v("C", "Mark C");
    graph.add_v("D", "Mark D");

    graph.add_e("A", "B", 7);
    graph.add_e("B", "C", 3);
    graph.add_e("C", "D", 5);
    graph.add_e("D", "A", 1);

    graph.edit_v("A", "New Mark A");
    graph.edit_e("A", "B", 10);
    graph.print_graph();

    cout << graph.get_first_index("D") << endl;
    cout << graph.get_next_index("D", 0) << endl;
    cout << graph.get_vertex("D", 0) << endl;

    return 0;
}
