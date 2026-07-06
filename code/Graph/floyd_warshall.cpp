#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int MAXN = 1e3 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

int dist[MAXN][MAXN];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    memset(dist, 0, sizeof(dist));

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];
    }

    for (int k = 0; k < n; k++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (dist[u][v] > dist[u][k] + dist[k][v])
                    dist[u][v] = dist[u][k] + dist[k][v];
}