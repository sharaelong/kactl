/**
 * Author:
 * Description: Check q is inside in simple polygon (not convex). It should not lie on the polygon. Polygon needs to be sorted but order doesn't matter.
 * Time: O(n \log n)
*/
#pragma once

bool is_inside(Point q, const vector<Point>& polygon) {
    int cross_cnt = 0;
    for (int i=0; i<polygon.size(); ++i) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i+1) % polygon.size()];
        if ((p1.y > q.y) != (p2.y > q.y)) {
            if (p2.y >= p1.y) {
                if ((q.x - p1.x) * (p2.y - p1.y) < (p2.x - p1.x) * (q.y - p1.y)) {
                    cross_cnt++;
                }
            } else {
                if ((q.x - p1.x) * (p2.y - p1.y) > (p2.x - p1.x) * (q.y - p1.y)) {
                    cross_cnt++;
                }
            }
        }
    }
    return cross_cnt % 2 != 0;
}
// return true even p is equal to p1 or p2
bool is_on_edge(Point p, Point p1, Point p2) {
    if (p1.x > p2.x) swap(p1, p2);
    if (p1.x <= p.x && p.x <= p2.x) {
        if (p1.x == p2.x) {
            if (min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y)) return true;
            else return false;
        }
        return ((p.x-p1.x) * (p2.y-p1.y) == (p.y-p1.y) * (p2.x-p1.x));
    }
    return false;
}
