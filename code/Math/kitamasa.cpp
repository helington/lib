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

    int qtd = L;//da recorrencia
    //aqui, vou dar o shift ( ou seja, vou dizer qual o termo inicial que eu REALMENTE TENHO) 
    //o ideal era q eu tivessse f(0)) 
    int shift = 0;
    for (int n = shift; n <= qtd; n++) {
        ll val = f(n);
        s.push_back(val);
    }

    vector<ll> rec;

    for(int i=0;i<L;i++){
        rec.push_back(r(i));//onde rec[i] = coef de f[n-i-1]; rec[0] = f[n-1], rec[1] = f[n-2];
    }


    vector<ll> init;

    for (int i = 0; i < (int)rec.size(); i++) {
        init.push_back(s[i]);
    }

    long long n;
    cin>>n;

    cout << "F[" << n << "] = " << linear_recurrence(init, rec, n - shift) << '\n';

}