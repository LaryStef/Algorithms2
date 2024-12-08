#include <iostream>
#include "find_paths.hpp"

using namespace std;

int main() {
    vector<string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    vector<vector<int>> weights_matrix = {
        { 0,  0, 10,  0,  0,  0 },
        { 0,  0,  0,  4, 13,  0 },
        { 0,  0,  0,  0,  0, 12 },
        { 8,  0,  0,  0,  0,  0 },
        { 0,  0,  0,  0,  0,  0 },
        { 0, 30,  0, 33, 13,  0 }
    };
    find_paths(weights_matrix, alphabet);

    return 0;
}
