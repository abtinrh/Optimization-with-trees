// Point.h
#ifndef POINT_H
#define POINT_H

#include <vector>
#include <iostream>
using namespace std;

class Point {
public:
    vector<double> coords;

    Point(const vector<double>& c) : coords(c) {}

    // بررسی اینکه this نقطه، نقطه‌ی دیگر را dominate می‌کند یا نه
    bool dominates(const Point& other) const {
        bool at_least_one_better = false;
        for (size_t i = 0; i < coords.size(); ++i) {
            if (coords[i] > other.coords[i]) return false;
            if (coords[i] < other.coords[i]) at_least_one_better = true;
        }
        return at_least_one_better;
    }

    void print() const {
        cout << "(";
        for (size_t i = 0; i < coords.size(); ++i) {
            cout << coords[i];
            if (i != coords.size() - 1) cout << ", ";
        }
        cout << ")";
    }
};

#endif // POINT_H
