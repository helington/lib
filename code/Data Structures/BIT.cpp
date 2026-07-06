#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

template<typename T>
struct BIT {
    int N;
    vector<T> bit;

    BIT(int n) : N(n+1), bit(n+1, 0) {}

    BIT(const vector<T> &v) : N(v.size() + 1), bit(v.size() + 1, 0) {
        for (int i = 0; i < v.size(); i++)
            bit[i + 1] = v[i];

        for (int i = 1; i < N; i++) {
            int parent = i + (i & -i);
            if (parent < N) bit[parent] += bit[i];
        }
    }

    void update(int idx, T val) {
        for (; idx < N; idx += idx & -idx)
            bit[idx] += val;
    }

    T query(int idx) {
        T ans = 0;
        for (; idx > 0; idx -= idx & -idx)
            ans += bit[idx];
        return ans;
    }

    T query(int l, int r) { return query(r) - query(l-1); }
};