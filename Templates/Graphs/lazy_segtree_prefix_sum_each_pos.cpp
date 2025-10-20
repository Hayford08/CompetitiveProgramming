#include <iostream>
using namespace std;

// Store prefix mn and mx up to and including index
struct SegmentTree {
private:
    static constexpr int INF = 1e9; 
    struct Node {
        int mn, mx, lazy;
        Node() : mn(0), mx(0), lazy(0) {}
        Node(int x) : mn(x), mx(x), lazy(0) {}
    };
    int n;
    vector<Node> tree;

    inline void apply(int pos, int val) {
        tree[pos].mn += val;
        tree[pos].mx += val;
        tree[pos].lazy += val;
    }

    inline void push(int pos, int lChild, int rChild) {
        int lazy = tree[pos].lazy;
        if (lazy != 0) {
            apply(lChild, lazy);
            apply(rChild, lazy);
            tree[pos].lazy = 0;
        }
    }

    inline void pull(int pos, int lChild, int rChild) {
        tree[pos].mn = min(tree[lChild].mn, tree[rChild].mn);
        tree[pos].mx = max(tree[lChild].mx, tree[rChild].mx);
    }

    // increase [l, r] by amt 
    inline void update(int tIdx, int tl, int tr, int l, int r, int val) {
        if (l > tr || tl > r) {
            return;
        }
        if (l <= tl && tr <= r) {
            apply(tIdx, val);
            return;
        }
        int tm = tl + (tr - tl) / 2;
        int lChild = tIdx + 1;
        int rChild = tIdx + 2 * (tm - tl + 1);
        push(tIdx, lChild, rChild);
        update(lChild, tl, tm, l, min(r, tm), val);
        update(rChild, tm + 1, tr, max(tm + 1, l), r, val);
        pull(tIdx, lChild, rChild);
    }

    // Return the prefix op from [l, r]
    inline Node query(int tIdx, int tl, int tr, int l, int r) {
        if (l > tr || tl > r) {
            return Node(INF);
        }
        if (l <= tl && tr <= r) {
            return tree[tIdx];
        }
        int tm = tl + (tr - tl) / 2;
        int lChild = tIdx + 1;
        int rChild = tIdx + 2 * (tm - tl + 1);
        push(tIdx, lChild, rChild);
        auto left = query(lChild, tl, tm, l, min(r, tm));
        auto right = query(rChild, tm + 1, tr, max(tm + 1, l), r);
        if (left.mn == INF) {
            return right;
        }
        if (right.mn == INF) {
            return left;
        }
        left.mn = min(left.mn, right.mn);
        left.mx = max(left.mx, right.mx);
        return left;
    }

    // find the first position within [l, r] with prefix as val
    int findFirst(int tIdx, int tl, int tr, int l, int r, int val) {
        if (l > tr || tl > r) {
            return INF;
        }
        if (val < tree[tIdx].mn || val > tree[tIdx].mx) {
            return INF;
        }
        if (l == r) {
            return l;
        }
        int tm = tl + (tr - tl) / 2;
        int lChild = tIdx + 1;
        int rChild = tIdx + 2 * (tm - tl + 1);
        push(tIdx, lChild, rChild);
        if (tree[lChild].mn <= val && val <= tree[lChild].mx) {
            return findFirst(lChild, tl, tm, l, min(tm, r), val);
        }
        return findFirst(rChild, tm + 1, tr, max(tm + 1, l), r, val);
    }

    inline int get(int tIdx, int tl, int tr, int pos) {
        if (tl == tr) {
            return tree[tIdx].mn;
        }
        int tm = tl + (tr - tl) / 2;
        int lChild = tIdx + 1;
        int rChild = tIdx + 2 * (tm - tl + 1);
        push(tIdx, tl, tr);
        if (pos <= tm) {
            return get(lChild, tl, tm, pos);
        }
        return get(rChild, tm + 1, tr, pos);
    }

public:
    SegmentTree(int n) : n(n), tree(2 * n + 1) {}

    inline void update(int l, int r, int val) {
        update(0, 0, n - 1, l, r, val);
    }

    inline Node query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    inline int findFirst(int l, int r, int val) {
        return findFirst(0, 0, n - 1, l, r, val);
    }

    inline int get(int pos) {
        return get(0, 0, n - 1, pos);
    }

    inline void print() {
        for (int i = 0; i < n; i++) {
            printf("%d ", get(i));
        }
        printf("\n");
    }
};