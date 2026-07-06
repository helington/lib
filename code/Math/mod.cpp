#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

const ll MOD = 1e9+7;
const int MAXN = 2e5 + 5;

ll mod_add(ll a,ll b){ return ((a%MOD) + (b%MOD)+2*MOD)%MOD; }
ll mod_sub(ll a,ll b){ return (((a%MOD) - (b%MOD))+2*MOD)%MOD; }
ll mod_mul(ll a,ll b){ return ((a%MOD) * (b%MOD))%MOD;}

ll norm(ll x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

ll fexp(ll a,ll b){
    ll res=1;
    a%=MOD;
    while(b){
        if(b&1) res=mod_mul(res,a);
        a=mod_mul(a,a);
        b>>=1;
    }
    return res;
}
// se for primo
ll inv_mod(ll a){
    return fexp(a, MOD-2);
}

ll mod_div(ll a,ll b){
    return mod_mul(a, inv_mod(b));
}

ll fact[MAXN], invFact[MAXN];

void precompute() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inv_mod(fact[i]);
    }
}

ll binomial(ll n, ll k) {
    if (k > n || k < 0) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}