#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

template<typename T>
struct SparseTable {
    int N, LOG;
    vector<vector<T>> table;

    // NOTE: For O(1) queries, the operation MUST be idempotent!
    T join(T a, T b) { return min(a, b); }

    SparseTable(vector<T> &v) : N(v.size()) {
        LOG = 32 - __builtin_clz(N);
        table.assign(LOG, vector<T>(N));
        
        for (int i = 0; i < N; i++)
            table[0][i] = v[i];

        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) - 1 < N; i++)
                table[j][i] = join(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
    }

    T query(int l, int r) {
        int j = 31 - __builtin_clz(r - l + 1);
        return join(table[j][l], table[j][r - (1 << j) + 1]);
    }
};