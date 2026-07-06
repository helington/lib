#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int INF = 1e9;

struct DSU {
    vector<int> id, sz, tim;
    int t=1;

    DSU(int n) : id(n), sz(n, 1), tim(n) { iota(id.begin(), id.end(), 0); }

    int find(int u, int q=INF) {
        if (id[u] == u or q < tim[u]) return u;
        return find(id[u], q);
    }

    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v], id[v] = u, tim[v] = t++;
        return true;
    }
};