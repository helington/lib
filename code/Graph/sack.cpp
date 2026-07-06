#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int MAXN = 1e5 + 5;
int sz[MAXN], color[MAXN], cnt[MAXN];
vector<int> adj[MAXN];

void build(int u, int p) {
    sz[u] = 1;

    // Remove o pai
    auto it = find(adj[u].begin(), adj[u].end(), p);
    if (it != adj[u].end()) adj[u].erase(it);

    for (auto &v : adj[u]) {
        build(v, u); sz[u] += sz[v];
        if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
    }
}

void compute(int u, int x, bool dont=true) {
    cnt[color[u]] += x;
    for (int i = dont; i < adj[u].size(); i++)
        compute(adj[u][i], x, false);
}

void solve(int u, bool keep=0) {
    for (int i = int(adj[u].size())-1; i >= 0; i--)
        solve(adj[u][i], !i);
    compute(u, 1);

    // RESPONDA A(S) QUERY(S) DO VÉRTICE 'u' EXATAMENTE AQUI!
    // Exemplo: ans[u] = cnt[cor_desejada];

    if (!keep) compute(u, -1, false);
}