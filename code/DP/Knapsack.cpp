#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

int n, W;
vector<pair<int, int>> a;

int solve() {
    vector<int> dp(W + 1);
    
    for (auto &[w, v] : a)
        for (int k = W - w; k >= 0; k--)
            dp[k + w] = max(dp[k + w], dp[k] + v);

    return 0;
}