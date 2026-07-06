#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
bool vis[MAXN], color[MAXN];

bool bipartite(int u) {
    vis[u] = true;

    for (int v : adj[u]) {
        if (!vis[v]) {
            color[v] = !color[u];
            if (!bipartite(v)) return false;
        }
        else if (color[u] == color[v]) return false;
    }

    return true;
}