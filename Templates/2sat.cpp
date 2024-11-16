#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TwoSAT {
public:
    TwoSAT(int n) : n(n), adj(2 * n), adj_rev(2 * n) {

    }

    // Function to solve the 2-SAT problem for given clauses
    bool solve(vector<vector<int>>& x) {
        // Initialize the graph
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                x[i][j] = convert(x[i][j]);
            }
        }

        // Add edges based on clauses
        for (int j = 0; j < n; j++) {
            int a = x[0][j];
            int b = x[1][j];
            int c = x[2][j];

            add_edge(a, b);              // ¬a -> b
            add_edge(b, a);              // ¬b -> a

            add_edge(a, c);              // ¬a -> c
            add_edge(c, a);              // ¬c -> a

            add_edge(b, c);              // ¬b -> c
            add_edge(c, b);              // ¬c -> b
        }

        // First pass to order vertices
        used.assign(2 * n, false);
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i]) {
                dfs1(i);
            }
        }
        comp.assign(2 * n, -1);
        reverse(order.begin(), order.end());
        int cnt = 0;
        for (auto v : order) {
            if (comp[v] == -1) {
                dfs2(v, cnt++);
            }
        }

        // Check for satisfiability
        assignment.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n]) {
                return false;
            }
            assignment[i] = comp[i] > comp[i + n];
        }
        return true;
    }

private:
    int n;
    vector<vector<int>> adj, adj_rev;
    vector<bool> used;
    vector<int> order, comp;
    vector<bool> assignment;

    // Function to convert x to appropriate index
    int convert(int x) {
        if (x < 0) return -x - 1;
        if (x > 0) return x - 1 + n;
        return x;
    }

    // Function to get the negation of x
    int nt(int x) {
        if (x >= n) return x - n;
        return x + n;
    }

    // Function to add ¬a -> b
    void add_edge(int a, int b){
        adj[nt(a)].push_back(b);
        adj_rev[b].push_back(nt(a));
    }

    // First DFS pass for ordering vertices
    void dfs1(int v) {
        used[v] = true;
        for (auto u : adj[v]) {
            if (!used[u]) {
                dfs1(u);
            }
        }
        order.push_back(v);
    }

    // Second DFS pass for assigning components
    void dfs2(int v, int k) {
        used[v] = true;
        comp[v] = k;
        for (auto u : adj_rev[v]) {
            if (comp[u] == -1) {
                dfs2(u, k);
            }
        }
    }
};