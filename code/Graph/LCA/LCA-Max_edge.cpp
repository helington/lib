#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int MAXN = 2e5 + 10;
const int LOG = 20;
int n, timer = 0;

int tin[MAXN], tout[MAXN];
vector<pair<int, ll>> adj[MAXN];
vector<int> depth(MAXN, 0);
int up[MAXN][LOG];
ll max_edge[MAXN][LOG];

void dfs(int u, int p, ll W) {
    tin[u] = timer++;
    up[u][0] = p;
    max_edge[u][0] = W;

    for (int i = 1; i < LOG; i++){
        up[u][i] = up[up[u][i-1]][i-1];
        max_edge[u][i] = max(max_edge[u][i-1], max_edge[up[u][i-1]][i-1]);
    }

    for (auto &[v, w] : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u, w);
    }

    tout[u] = timer - 1;
}

pair<int, ll> kth_anc(int u, int k) {
    ll ans = 0;
    for (int i = 0; (1 << i) <= k; i++)
        if ((1 << i) & k) {
            ans = max(ans, max_edge[u][i]);
            u = up[u][i];
        }
    return {u, ans};
}

ll query(int u, int v) {
    ll ans = 0;

    if (depth[u] < depth[v]) swap(u, v);

    auto [nu, nw] = kth_anc(u, depth[u] - depth[v]);
    u = nu, ans = nw;

    if (u == v) return ans;

    for (int i = LOG-1; i >= 0; i--)
        if (up[u][i] != up[v][i]) {
            ans = max({ans, max_edge[u][i], max_edge[v][i]});
            u = up[u][i], v = up[v][i];
        }

    return max({ans, max_edge[u][0], max_edge[v][0]});
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dfs(1, 0, 0);

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        cout << query(u, v) << endl;
    }

    return 0;
}
