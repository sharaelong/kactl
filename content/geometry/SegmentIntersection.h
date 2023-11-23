/**
 * Author:
 * Description:
 * Usage: intersect(..) returns type of segment intersection defined in enum. \\
find_point(..) 0: not intersect, -1: infinity, 1: cross. Return value is flag, xp, xq, yp, yq given in fraction. xp is numer, xq is domi.
 */
#pragma once

int sgn(ll x) {
    return (x > 0 ? 1 : (x < 0 ? -1 :0));
}

enum Intersection {
    NONE,
    ENDEND,
    ENDMID,
    MID,
    INF
};

int intersect(Point s1, Point e1, Point s2, Point e2) {
    int t1 = sgn((e1-s1) ^ (s2-e1));
    int t2 = sgn((e1-s1) ^ (e2-e1));
    if (t1 == 0 && t2 == 0) {
        if (e1 < s1) swap(s1, e1);
        if (e2 < s2) swap(s2, e2);
        if (e1 == s2 || s1 == e2) return ENDEND;
        else return (e1 < s2 || e2 < s1) ? NONE : INF;
    } else {
        int t3 = sgn((e2-s2) ^ (s1-e2));
        int t4 = sgn((e2-s2) ^ (e1-e2));
        if (t1*t2 == 0 && t3*t4 == 0) return ENDEND;
        if (t1 != t2 && t3 != t4) {
            return (t1*t2 == 0 || t3*t4 == 0 ? ENDMID : MID);
        } else {
            return NONE;
        }
    }
}

using T = __int128_t; // T <= O(COORD^3)
tuple<int, T, T, T, T> find_point(Point s1, Point e1, Point s2, Point e2) {
    int res = intersect(s1, e1, s2, e2);
    if (res == NONE) return {0, 0, 0, 0, 0};
    if (res == INF) return {-1, 0, 0, 0, 0};
    auto det = (e1-s1)^(e2-s2);
    if (!det) {
        if(s1 > e1) swap(s1, e1);
        if(s2 > e2) swap(s2, e2);
        if(e1 == s2) return {1, e1.x, 1, e1.y, 1};
        else return {1, e2.x, 1, e2.y, 1};
    }
    T p = (s2-s1)^(e2-s2), q = det;
    T xp = s1.x*q + (e1.x-s1.x)*p, xq = q;
    T yp = s1.y*q + (e1.y-s1.y)*p, yq = q;
    if (xq < 0) xp = -xp, xq = -xq;
    if (yq < 0) yp = -yp, yq = -yq;
    T xg = gcd(abs(xp), xq), yg = gcd(abs(yp), yq);
    return {1, xp/xg, xq/xg, yp/yg, yq/yg};
}
