#include <vector>
#include <iostream>
#include <functional>
using namespace std;

template<typename T>
struct SegTree {
    vector<T> tree, lazy, arr;
    int n;
    T identity;
    function<T(T, T)> combine;
    function<T(T, T, int)> propagate_func;

    // Constructor to initialize the segment tree with a given size
    SegTree(int sz, T identity, function<T(T, T)> combine, function<T(T, T, int)> propagate_func)
        : n(sz), identity(identity), combine(combine), propagate_func(propagate_func) {
        tree.resize(4 * sz, identity);
        lazy.resize(4 * sz, 0);
    }

    // Constructor to initialize the segment tree with an existing array
    SegTree(vector<T>& inputArr, T identity, function<T(T, T)> combine, function<T(T, T, int)> propagate_func)
        : identity(identity), combine(combine), propagate_func(propagate_func) {
        n = inputArr.size();
        arr = inputArr;
        tree.resize(4 * n, identity);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    // Function to build the segment tree
    void build(int tIdx, int l, int r) {
        if (l == r) {
            tree[tIdx] = arr[l];
            return;
        }
        int m = l + (r - l) / 2;
        int lc = tIdx * 2 + 1;
        int rc = tIdx * 2 + 2;
        build(lc, l, m);
        build(rc, m + 1, r);
        tree[tIdx] = combine(tree[lc], tree[rc]);
    }

    // Function to propagate updates to children
    void propagate(int tIdx, int l, int r) {
        if (lazy[tIdx] != 0) {
            tree[tIdx] = propagate_func(tree[tIdx], lazy[tIdx], r - l + 1);
            if (l != r) { 
                lazy[tIdx * 2 + 1] = propagate_func(lazy[tIdx * 2 + 1], lazy[tIdx], 1);
                lazy[tIdx * 2 + 2] = propagate_func(lazy[tIdx * 2 + 2], lazy[tIdx], 1);
            }
            lazy[tIdx] = 0;
        }
    }

    // Function to update a range with lazy propagation
    void range_update(int tIdx, int tl, int tr, int l, int r, T val) {
        propagate(tIdx, tl, tr); 
        if (tl > r || tr < l) { 
            return;
        }
        if (l <= tl && tr <= r) { 
            lazy[tIdx] = propagate_func(lazy[tIdx], val, 1);
            propagate(tIdx, tl, tr);
            return;
        }
        // Partial overlap
        int tm = tl + (tr - tl) / 2;
        range_update(tIdx * 2 + 1, tl, tm, l, r, val);
        range_update(tIdx * 2 + 2, tm + 1, tr, l, r, val);
        tree[tIdx] = combine(tree[tIdx * 2 + 1], tree[tIdx * 2 + 2]);
    }

    // Function to query a range with lazy propagation
    T range_query(int tIdx, int tl, int tr, int l, int r) {
        propagate(tIdx, tl, tr); 
        if (tl > r || tr < l) { 
            return identity; 
        }
        if (l <= tl && tr <= r) {
            return tree[tIdx];
        }
        // Partial overlap
        int tm = tl + (tr - tl) / 2;
        T leftQuery = range_query(tIdx * 2 + 1, tl, tm, l, r);
        T rightQuery = range_query(tIdx * 2 + 2, tm + 1, tr, l, r);
        return combine(leftQuery, rightQuery);
    }

    // Function to update a specific position
    void point_update(int tIdx, int tl, int tr, int pos, T val) {
        propagate(tIdx, tl, tr); // Apply pending updates
        if (tl == tr) {
            tree[tIdx] = val;
            return;
        }
        int tm = tl + (tr - tl) / 2;
        if (pos <= tm) {
            point_update(tIdx * 2 + 1, tl, tm, pos, val);
        } else {
            point_update(tIdx * 2 + 2, tm + 1, tr, pos, val);
        }
        tree[tIdx] = combine(tree[tIdx * 2 + 1], tree[tIdx * 2 + 2]); 
    }

    // Function to query a specific position
    T point_query(int tIdx, int tl, int tr, int pos) {
        propagate(tIdx, tl, tr); // Apply pending updates
        if (tl == tr) {
            return tree[tIdx];
        }
        int tm = tl + (tr - tl) / 2;
        if (pos <= tm) {
            return point_query(tIdx * 2 + 1, tl, tm, pos);
        } else {
            return point_query(tIdx * 2 + 2, tm + 1, tr, pos);
        }
    }

    // Public wrappers for the range update, range query, point update, and point query functions
    void range_update(int l, int r, T val) {
        range_update(0, 0, n - 1, l, r, val);
    }

    T range_query(int l, int r) {
        return range_query(0, 0, n - 1, l, r);
    }

    void point_update(int pos, T val) {
        point_update(0, 0, n - 1, pos, val);
    }

    T point_query(int pos) {
        return point_query(0, 0, n - 1, pos);
    }
};

// Example usage:
// Define the combination and propagation functions for sum operation
auto combine_sum = [](int a, int b) { return a + b; };
auto propagate_sum = [](int current, int value, int length) { return current + value * length; };

// Example usage with sum operation
int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    SegTree<int> segtree(arr, 0, combine_sum, propagate_sum);

    // Range update: add 10 to all elements in the range [1, 3]
    segtree.range_update(1, 3, 10);

    // Range query: sum of elements in the range [1, 4]
    int result = segtree.range_query(1, 4);

    // Point update: set the element at index 2 to 7
    segtree.point_update(2, 7);

    // Point query: get the element at index 2
    int value = segtree.point_query(2);

    std::cout << result << " " << value << "\n";

    return 0;
}

/*

class SegmentTree {
    struct Node {
        long long both;
        long long left;
        long long right;
        long long none;
        Node() : both(0ll), left(0ll), right(0ll), none(0ll) {}
        
        Node(long long x) : both(max(0ll, x)), left(0ll), right(0ll), none(0ll) {}
    };

    vector<Node> tree;
    int n;

public:
    SegmentTree(int size) : n(size) {
        tree.resize(4 * size);
    }

    void build(const vector<int>& nums, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = Node(nums[tl]);
        } else {
            int tm = tl + (tr - tl) / 2;
            build(nums, v * 2 + 1, tl, tm);
            build(nums, v * 2 + 2, tm + 1, tr);
            tree[v] = combine(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = Node(new_val);
        } else {
            int tm = tl + (tr - tl) / 2;
            if (pos <= tm) {
                update(v * 2 + 1, tl, tm, pos, new_val);
            } else {
                update(v * 2 + 2, tm + 1, tr, pos, new_val);
            }
            tree[v] = combine(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    Node query(int v, int tl, int tr, int l, int r) {
        if (tl > r || tr < l){
            return Node();
        }
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        int tm = tl + (tr - tl) / 2;
        Node left_query = query(v * 2 + 1, tl, tm, l, min(r, tm));
        Node right_query = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        return combine(left_query, right_query);
    }

    Node combine(const Node& a, const Node& b) {
        Node res;
        res.both = max({a.left + b.right, 
                        a.both + b.right, 
                        a.left + b.both});
        res.right = max({a.none + b.right,
                        a.right + b.right, 
                        a.none + b.both});
        res.left = max({a.left + b.none,
                       a.left + b.left,
                       a.both + b.none});
        res.none = max({a.right + b.none,
                       a.none + b.left,
                       a.none + b.none});
        return res;
    }

    void build(const vector<int>& nums) {
        build(nums, 0, 0, n - 1);
    }

    void update(int pos, int new_val) {
        update(0, 0, n - 1, pos, new_val);
    }

    Node query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

[2,15,14,18] -> 35
*/

