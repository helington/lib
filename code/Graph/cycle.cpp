#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
bool vis[MAXN], color[MAXN];
vector<int> cycle;

int get_cycle(int u, int p=-1) {
    if (vis[u]) return u;
    vis[u] = true;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        int last = get_cycle(v, u);

        if (last == -2) return -2;
        if (last != -1) {
            cycle.push_back(u);
            if (u == last) return -2;
            else return last;
        }
    }

    return -1;
}