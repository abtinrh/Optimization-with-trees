// main.cpp
#include "BJRTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    ifstream infile("data.txt");
    if (!infile.is_open()) {
        cerr << "Error: Could not open data.txt file." << endl;
        return 1;
    }

    vector<Point> points;
    string line;
    int dimension = -1;

    while (getline(infile, line)) {
        istringstream iss(line);
        vector<double> coords;
        double val;
        while (iss >> val) {
            coords.push_back(val);
        }
        if (coords.empty()) continue;
        if (dimension == -1) dimension = coords.size();
        if ((int)coords.size() != dimension) {
            cerr << "Error: Inconsistent dimension in line: " << line << endl;
            continue;
        }
        points.emplace_back(coords);
    }

    infile.close();

    if (dimension == -1) {
        cerr << "Error: No valid data found in file." << endl;
        return 1;
    }

    BJRTree tree(dimension);
    for (const auto& pt : points) {
        tree.insert(pt);
    }

    cout << "\nBefore ejection:\n";
    tree.print_tree();

    // Case 1: remove leaf node
    cout << "\nRemoving point (4, 1)...\n";
    tree.remove(Point({4, 1}));
    tree.print_tree();

    // Case 2: remove internal node
    cout << "\nRemoving point (0, 7)...\n";
    tree.remove(Point({0, 7}));
    tree.print_tree();

    // Case 3: remove root node
    cout << "\nRemoving root point (2, 3)...\n";
    tree.remove(Point({2, 3}));
    tree.print_tree();

    // Flush lazy buffer
    cout << "\nFlushing lazy buffer...\n";
    tree.flush_lazy();
    tree.print_tree();

    // NDCache test:
    cout << "\n--- NDCache Test ---\n";
    Point dominator({2, 2});
    Point dominated({5, 5});

    tree.insert(dominator); // inserted as root
    tree.insert(dominated); // dominated by (2, 2), goes to NDCache
    tree.print_tree();

    cout << "\nRemoving dominator point (2, 2)...\n";
    tree.remove(dominator); // should flush NDCache
    tree.print_tree();

    return 0;
}