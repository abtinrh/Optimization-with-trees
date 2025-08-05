// NDCache.h
#ifndef ND_CACHE_H
#define ND_CACHE_H

#include "Point.h"
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class NDCache {
private:
    vector<Point> skyline_points;

public:
    // افزودن یک نقطه به کش در صورت نیاز
    void try_insert(const Point& pt) {
        // اگر نقطه جدید توسط یکی از نقاط کش dominate شود، آن را نادیده می‌گیریم
        for (const auto& p : skyline_points) {
            if (p.dominates(pt)) return;
        }

        // حذف تمام نقاطی که توسط نقطه جدید dominate می‌شوند
        skyline_points.erase(
            remove_if(skyline_points.begin(), skyline_points.end(),
                [&](const Point& p) { return pt.dominates(p); }),
            skyline_points.end()
        );

        // افزودن نقطه جدید
        skyline_points.push_back(pt);
    }

    // چاپ نقاط کش
    void print_cache() const {
        cout << "\nSkyline Cache:\n";
        for (const auto& p : skyline_points) {
            p.print();
            cout << "\n";
        }
    }
};

#endif // ND_CACHE_H
