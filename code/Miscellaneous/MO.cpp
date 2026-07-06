#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

const int BLOCK = 450;
int q;

struct Query {
    int l, r, idx;
    bool operator < (const Query &o) const {
        int b1 = l / BLOCK, b2 = o.l / BLOCK;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? (r < o.r) : (r > o.r);
    }
};

vector<ll> MO(vector<Query> &queries) {
    vector<ll> ans(q);
    sort(queries.begin(), queries.end());

    int L=0, R=-1;

    auto add = [&](int idx) -> void {};
    auto remove = [&](int idx) -> void {};
    auto get_ans = [&]() -> int {};

    for (auto [l, r, idx] : queries) {
        while (l < L) add(--L);
        while (r > R) add(++R);
        while (l > L) remove(L++);
        while (r < R) remove(R--);
        ans[idx] = get_ans();
    }

    return ans;
}