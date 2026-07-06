#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int MAXN = 2e5 + 5;
int n;

vector<int> adj[MAXN];

vector<int> toposort() {
    vector<int> indegree(n, 0);

    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) indegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> ord;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        ord.push_back(u);

        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }

    return ord;
}