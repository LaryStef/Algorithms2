#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class DirectedGraph {
private:
    struct Vertex {
        int index;
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
        return -1;
    }

public:
    void add_v(string name, string mark) {
        // Проверяем, существует ли вершина с таким именем
        for (Vertex vertex : vertices) {
            if (vertex.name == name) {
                throw invalid_argument("Vertex with given name already exists.");
            }
        }

        // Добавляем новую вершину
        int index = vertices.size();

        Vertex newVertex;
        newVertex.index = index; // Присваиваем индекс как текущий размер списка вершин
        newVertex.name = name;
        newVertex.mark = mark;
        vertices.push_back(newVertex);

        incidenceMatrix.push_back(vector<int>());
        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            incidenceMatrix[index].push_back(0);
        }
    }

    void add_e(string v, string w, int c) {
        int from = findVertexIndex(v);
        int to = findVertexIndex(w);
        if (from == -1 || to == -1) {
            throw invalid_argument("Vertex with given name does not exist.");
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
        int index = findVertexIndex(name);
        if (index == -1) {
            throw invalid_argument("Vertex with given name does not exist.");
        }

        for (int incidence : incidenceMatrix[index]) {
            if (incidence != 0) {
                cout << incidence << endl;
                throw invalid_argument("Vertex has incident edges.");
            }
        }
        vertices.erase(vertices.begin() + index);
        incidenceMatrix.erase(incidenceMatrix.begin() + index);
    }

    void del_e(string v, string w) {
        if (incidenceMatrix.size() == 0 || incidenceMatrix[0].size() == 0) {
            throw invalid_argument("Cannot delete edge from empty graph.");
        }

        int from = findVertexIndex(v);
        int to = findVertexIndex(w);
        if (from == -1 || to == -1) {
            throw invalid_argument("Edge with given name does not exist.");
        }

        for (int i = 0; i < incidenceMatrix[0].size(); ++i) {
            if (incidenceMatrix[from][i] != 0 && incidenceMatrix[to][i] != 0) {
                for (int j = 0; j < incidenceMatrix.size(); ++j) {
                    incidenceMatrix[j].erase(incidenceMatrix[j].begin() + i);
                }
            }
        }
    }

    void printGraph() {
        cout << "Vertices:\n";
        for (Vertex vertex : vertices) {
            cout << vertex.index << ": " << vertex.name << " (" << vertex.mark << ")\n";
        }
        cout << "\nIncidence Matrix:\n";
        for (vector<int> row : incidenceMatrix) {
            for (int weight : row) {
                cout << weight << " ";
            }
            cout << "\n";
        }
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

    graph.del_e("A", "B");
    graph.printGraph();
    graph.del_e("B", "C");
    graph.printGraph();
    graph.del_v("B");

    graph.printGraph();

    return 0;
}
