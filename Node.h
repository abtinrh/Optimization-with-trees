// Node.h
#ifndef NODE_H
#define NODE_H

#include "Point.h"
#include <memory>
#include <vector>
using namespace std;

class Node {
public:
    Point point;
    vector<shared_ptr<Node>> children;

    Node(const Point& pt) : point(pt) {}
};

#endif // NODE_H
