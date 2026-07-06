#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

struct Node {
    ll val;

    Node() : val(0) {}
    Node(ll v) : val(v) {}
};

Node merge(Node vl, Node vr) { return Node(vl.val + vr.val); }

struct SegTree {
    int N;
    vector<Node> seg;

    SegTree(int n) : N(n), seg(4 * n) {}

    SegTree(vector<ll> &v) : N(v.size()), seg(4 * v.size()) {
        build(v, 1, 0, N - 1);
    }

    void build(vector<ll> &v, int p, int l, int r) {
        if (l == r) {
            seg[p] = Node(v[l]);
            return;
        }

        int m = (l + r) / 2;

        build(v, 2 * p, l, m);
        build(v, 2 * p + 1, m + 1, r);
        
        seg[p] = merge(seg[2 * p], seg[2 * p + 1]);
    }

    Node query(int a, int b, int p, int l, int r) {
        if (b < l or r < a) return Node();
        if (a <= l and r <= b) return seg[p];

        int m = (l + r) / 2;

        return merge(query(a, b, 2 * p, l, m), 
                    query(a, b, 2 * p + 1, m + 1, r));
    }

    
    void update(int idx, ll val, int p, int l, int r) {
        if (idx < l or r < idx) return;
        if (l == r) {
            seg[p] = val;
            return;
        }
        
        int m = (l + r) / 2;
        
        update(idx, val, 2 * p, l, m);
        update(idx, val, 2 * p + 1, m + 1, r);
        
        seg[p] = merge(seg[2 * p], seg[2 * p + 1]);
    }
    
    ll query(int a, int b) { return query(a, b, 1, 0, N - 1).val; }
    void update(int idx, ll val) { update(idx, val, 1, 0, N - 1); }
};