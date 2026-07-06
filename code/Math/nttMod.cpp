#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

const ll mod = 998244353;
const ll root = 62;

ll fexp(ll a, ll e) {
    ll ans = 1;

    while (e) {
        if (e & 1) ans = ans * a % mod;
        a = a * a % mod;
        e >>= 1;
    }

    return ans;
}

int next_pow2(int x) {
    int n = 1;
    while (n < x) n <<= 1;
    return n;
}

void ntt(vector<ll>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);

    static vector<ll> rt(2, 1);

    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);

        ll z[] = {1, fexp(root, mod >> s)};

        for (int i = k; i < 2 * k; i++) {
            rt[i] = rt[i / 2] * z[i & 1] % mod;
        }
    }

    vector<int> rev(n);

    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    }

    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll z = rt[j + k] * a[i + j + k] % mod;
                ll &ai = a[i + j];

                a[i + j + k] = ai - z + (z > ai ? mod : 0);
                ai += z - (ai + z >= mod ? mod : 0);
            }
        }
    }
}

void intt(vector<ll>& a) {
    int n = a.size();

    reverse(a.begin() + 1, a.end());

    ntt(a);

    ll inv_n = fexp(n, mod - 2);

    for (ll &x : a) {
        x = x * inv_n % mod;
    }
}

void ntt2d(vector<vector<ll>>& a) {
    int n = a.size();
    int m = a[0].size();

    for (int i = 0; i < n; i++) {
        ntt(a[i]);
    }

    vector<ll> col(n);

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            col[i] = a[i][j];
        }

        ntt(col);

        for (int i = 0; i < n; i++) {
            a[i][j] = col[i];
        }
    }
}

void intt2d(vector<vector<ll>>& a) {
    int n = a.size();
    int m = a[0].size();

    for (int i = 0; i < n; i++) {
        intt(a[i]);
    }

    vector<ll> col(n);

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            col[i] = a[i][j];
        }

        intt(col);

        for (int i = 0; i < n; i++) {
            a[i][j] = col[i];
        }
    }
}

ll norm(ll x) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

vector<vector<ll>> conv2d_ntt(
    const vector<vector<ll>>& A,
    const vector<vector<ll>>& B
) {
    if (A.empty() || B.empty()) return {};
    if (A[0].empty() || B[0].empty()) return {};

    int n = A.size();
    int m = A[0].size();

    int p = B.size();
    int q = B[0].size();

    int H = next_pow2(n + p - 1);
    int W = next_pow2(m + q - 1);

    vector<vector<ll>> FA(H, vector<ll>(W, 0));
    vector<vector<ll>> FB(H, vector<ll>(W, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            FA[i][j] = norm(A[i][j]);
        }
    }

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            FB[i][j] = norm(B[i][j]);
        }
    }

    ntt2d(FA);
    ntt2d(FB);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            FA[i][j] = FA[i][j] * FB[i][j] % mod;
        }
    }

    intt2d(FA);

    vector<vector<ll>> ans(n + p - 1, vector<ll>(m + q - 1));

    for (int i = 0; i < n + p - 1; i++) {
        for (int j = 0; j < m + q - 1; j++) {
            ans[i][j] = FA[i][j];
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<ll>> A(n, vector<ll>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }

    int p, q;
    cin >> p >> q;

    vector<vector<ll>> B(p, vector<ll>(q));

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            cin >> B[i][j];
        }
    }

    auto C = conv2d_ntt(A, B);

    cout << C.size() << ' ' << C[0].size() << '\n';

    for (int i = 0; i < (int)C.size(); i++) {
        for (int j = 0; j < (int)C[i].size(); j++) {
            cout << C[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}