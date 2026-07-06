#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9+7;

ll mod_add(ll a,ll b){ return (a%MOD + b%MOD)%MOD; }
ll mod_sub(ll a,ll b){ return ((a%MOD - b%MOD)+MOD)%MOD; }
ll mod_mul(ll a,ll b){ return ((a%MOD) * (b%MOD))%MOD; }

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

ll inv_mod(ll a){
    return fexp(a, MOD-2);
}

ll brute(ll n){
    return 0;
}

vector<ll> berlekamp_massey(const vector<ll>& s) {
    vector<ll> C = {1};
    vector<ll> B = {1};

    int L = 0;
    int m = 1;
    ll b = 1;

    for (int n = 0; n < (int)s.size(); n++) {
        ll d = 0;

        for (int i = 0; i <= L; i++) {
            d = mod_add(d , mod_mul(C[i] , s[n - i]));
        }

        if (d == 0) {
            m++;
            continue;
        }

        vector<ll> T = C;
        ll coef = mod_mul(d, inv_mod(b));

        if ((int)C.size() < (int)B.size() + m) {
            C.resize(B.size() + m, 0);
        }

        for (int i = 0; i < (int)B.size(); i++) {
            C[i + m] = mod_sub(C[i + m], mod_mul(coef, B[i]));
        }

        if (2 * L <= n) {
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        } else {
            m++;
        }
    }

    vector<ll> rec(L);

    for (int i = 1; i <= L; i++) {
        rec[i - 1] = mod_sub(MOD, C[i]);
    }

    return rec;
}

vector<ll> combine(vector<ll> a, vector<ll> b, const vector<ll>& rec) {
    int L = rec.size();

    vector<ll> tmp(2 * L, 0);

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            tmp[i + j] = mod_add(tmp[i + j], mod_mul(a[i] , b[j]));
        }
    }

    for (int i = 2 * L - 2; i >= L; i--) {
        for (int j = 1; j <= L; j++) {
            tmp[i - j] = mod_add(tmp[i - j], mod_mul(tmp[i] ,rec[j - 1]));
        }
    }

    tmp.resize(L);
    return tmp;
}


ll linear_recurrence(const vector<ll>& init, const vector<ll>& rec, long long n) {
    int L = rec.size();

    if (n < (int)init.size()) {
        return init[n] % MOD;
    }

    vector<ll> pol(L, 0);
    vector<ll> e(L, 0);

    pol[0] = 1;

    if (L == 1) {
        e[0] = rec[0];
    } else {
        e[1] = 1;
    }

    while (n > 0) {
        if (n & 1) {
            pol = combine(pol, e, rec);
        }

        e = combine(e, e, rec);
        n >>= 1;
    }

    ll ans = 0;

    for (int i = 0; i < L; i++) {
        ans = mod_add(ans,mod_mul(pol[i] , init[i]));
    }

    return ans;
}

int main() {
    vector<ll> s;

    int qtd = 100;
    //aqui, vou dar o shift ( ou seja, vou dizer qual o termo inicial que eu REALMENTE TENHO) 
    //o ideal era q eu tivessse f(0)) 
    int shift;
    for (int n = shift; n <= qtd; n++) {
        ll val = brute(n);

        //aqui, vai colocar até onde quer que o algoritmo use, pra poder testar se ta legal dps
        if(n<=10) s.push_back(val);

        cout << "F(" << n << ") = " << val << '\n';
    }
    for (ll x : s) {
        cout << "s.push_back("<<x  << ")"<< "; "<<endl;
    }

    vector<ll> rec = berlekamp_massey(s);

    cout << "Ordem da recorrencia: " << rec.size() << '\n';

    cout << "Coeficientes:\n";
    for (ll x : rec) {
        cout << "rec.push_back("<<x  << ")"<< "; "<<endl;
    }
    cout << endl;

    vector<ll> init;

    for (int i = 0; i < (int)rec.size(); i++) {
        init.push_back(s[i]);
    }

    long long n;

    cout << "Digite n: ";
    cin >> n;
    cout << "F[" << n << "] = " << linear_recurrence(init, rec, n - shift) << '\n';

}