/**
 * Author:
 * Description: Possible to sort without consider quadrant. If angle is same then sorted by distance.
 */
#pragma once

sort(a, a+n, [&](const pnt &a, const pnt &b){
    if((pi(a.x, a.y) > pi(0, 0)) ^ (pi(b.x, b.y) > pi(0, 0))) return pi(a.x, a.y) > pi(b.x, b.y);
    if(ccw(a, b) != 0) return ccw(a, b) > 0;
    return hypot(a) < hypot(b);
});
