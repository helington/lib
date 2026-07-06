#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int bit = 0; bit < n; bit++) {
            if (mask & (1 << bit)) {
                // opera no subconjunto
            }
        }
        // fala sobre o subconjunto completo
    }

    return 0;
}