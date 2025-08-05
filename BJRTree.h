// BJRTree.h
#ifndef BJR_TREE_H
#define BJR_TREE_H

#include "Node.h"
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

class BJRTree {
private:
    shared_ptr<Node> root;
    int dimension;
    std::vector<Point> lazyBuffer;

public:
    BJRTree(int dim) : root(nullptr), dimension(dim) {}

    void insert(const Point& pt) {
        if (!root) {
            root = make_shared<Node>(pt);
            std::cout << "Inserted root point: ";
            pt.print();
            std::cout << "\n";
            return;
        }
        insert_recursive(root, pt);
    }

    void remove(const Point& pt) {
        remove_recursive(nullptr, root, pt);
    }

    void flush_lazy() {
        std::cout << "\nFlushing lazy buffer...\n";
        for (const auto& pt : lazyBuffer) {
            std::cout << "Inserting lazy point: ";
            pt.print();
            std::cout << "\n";

            if (!root) {
                root = make_shared<Node>(pt);
                std::cout << "Inserted as new root.\n";
            } else {
                insert(pt);
            }
        }
        lazyBuffer.clear();
    }

private:
    bool insert_recursive(shared_ptr<Node> node, const Point& pt) {
        if (node->point.dominates(pt)) {
            std::cout << "Rejected point "; pt.print(); std::cout << " — dominated by "; node->point.print(); std::cout << "\n";
            return true;
        }

        if (pt.dominates(node->point)) {
            std::cout << "Replacing point "; node->point.print(); std::cout << " with "; pt.print(); std::cout << "\n";
            node->point = pt;
            node->children.clear();
            return true;
        }

        bool inserted = false;
        for (auto& child : node->children) {
            if (insert_recursive(child, pt)) {
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            std::cout << "Inserted point as child of "; node->point.print(); std::cout << ": "; pt.print(); std::cout << "\n";
            node->children.push_back(make_shared<Node>(pt));
            return true;
        }

        return inserted;
    }

    void collect_subtree_points(shared_ptr<Node> node) {
        if (!node) return;
        lazyBuffer.push_back(node->point);
        for (const auto& child : node->children) {
            collect_subtree_points(child);
        }
    }

    void remove_recursive(shared_ptr<Node> parent, shared_ptr<Node> node, const Point& pt) {
        if (!node) return;

        if (node->point.coords == pt.coords) {
            collect_subtree_points(node); // ← ثبت کل زیر درخت، شامل خود گره

            if (parent) {
                parent->children.erase(remove_if(parent->children.begin(), parent->children.end(),
                    [&](const shared_ptr<Node>& n) { return n->point.coords == pt.coords; }),
                    parent->children.end());
            } else {
                root = nullptr;
            }
            return;
        }

        for (auto& child : node->children) {
            remove_recursive(node, child, pt);
        }
    }

public:
    void print_tree() const {
        std::cout << "BJR-Tree:\n";
        print_recursive(root, 0);
    }

private:
    void print_recursive(shared_ptr<Node> node, int depth) const {
        if (!node) return;
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        node->point.print();
        std::cout << "\n";
        for (const auto& child : node->children) {
            print_recursive(child, depth + 1);
        }
    }
};

#endif // BJR_TREE_H
