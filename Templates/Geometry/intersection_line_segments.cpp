#include <iostream>
using namespace std;

const int CCW = -1;  // Counterclockwise
const int COL = 0;   // Collinear
const int CW = 1;    // Clockwise

/**
 * Determines the orientation of the triplet (p, q, r).
 * 
 * @param p[] - The first point of the triplet.
 * @param q[] - The second point of the triplet.
 * @param r[] - The third point of the triplet.
 * @return -1 if the points are counterclockwise, 0 if collinear, and 1 if clockwise.
 */
int orientation(int p[], int q[], int r[]) {
    long long dir = 1ll * (p[0] - r[0]) * (q[1] - r[1]) - 1ll * (p[1] - r[1]) * (q[0] - r[0]);
    return dir == 0 ? COL : (dir > 0 ? CW : CCW);
}

/**
 * Checks if a point x lies within the range defined by points s and t.
 * 
 * @param s - One endpoint of the range.
 * @param t - The other endpoint of the range.
 * @param x - The point to check.
 * @return true if x lies within the range [min(s, t), max(s, t)], false otherwise.
 */
bool overlaps(int s, int t, int x) {
    return min(s, t) <= x && x <= max(s, t);
}

/**
 * Checks if point r lies on the segment defined by points p and q.
 * 
 * @param p[] - One endpoint of the segment.
 * @param q[] - The other endpoint of the segment.
 * @param r[] - The point to check.
 * @return true if r lies on the segment pq, false otherwise.
 */
bool on_segment(int p[], int q[], int r[]) {
    return overlaps(p[0], q[0], r[0]) && overlaps(p[1], q[1], r[1]);
}

/**
 * Determines if the segment p1q1 intersects with the segment p2q2.
 * 
 * @param p1[] - One endpoint of the first segment.
 * @param q1[] - The other endpoint of the first segment.
 * @param p2[] - One endpoint of the second segment.
 * @param q2[] - The other endpoint of the second segment.
 * @return true if the segments intersect, false otherwise.
 */
bool doIntersect(int p1[], int q1[], int p2[], int q2[]) {
    int p1q1p2 = orientation(p1, q1, p2);
    int p1q1q2 = orientation(p1, q1, q2);
    int p2q2p1 = orientation(p2, q2, p1);
    int p2q2q1 = orientation(p2, q2, q1);
    
    if (p1q1p2 != p1q1q2 && p2q2p1 != p2q2q1) {
        return true;
    }
    
    return (p1q1p2 == 0 && on_segment(p1, q1, p2)) || 
           (p1q1q2 == 0 && on_segment(p1, q1, q2)) || 
           (p2q2p1 == 0 && on_segment(p2, q2, p1)) || 
           (p2q2q1 == 0 && on_segment(p2, q2, q1));
}
