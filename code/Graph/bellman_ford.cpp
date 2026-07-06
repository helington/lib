#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

int n;
const ll INF = 1e18; // based on question's contraints

vector<ll> bellmanFord(vector<vector<pair<int, ll>>> &adj, int b) {
    vector<ll> dist(n, INF);
    dist[b] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool any_update = false;

        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;

            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    any_update = true;
                }
            }
        }

        if (!any_update) break;
    }

    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;

        for(auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                return {};
            }
        }
    }

    return dist;
}