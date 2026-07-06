using CD = complex<double>;
const CD Cero = CD(0, 0);

void fft(vector<CD>& a) {
    int n = a.size(), L = 31 - __builtin_clz(n);

    static vector<complex<long double>> R(2, 1);
    static vector<CD> rt(2, 1);

    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acosl(-1.0L) / k);
        for (int i = k; i < 2*k; i++) {
            rt[i] = R[i] = (i & 1) ? R[i/2] * x : R[i/2];
        }
    }

    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i/2] | (i & 1) << L) / 2;
    }

    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2*k) {
            for (int j = 0; j < k; j++) {
                CD z = rt[j+k] * a[i+j+k];
                a[i+j+k] = a[i+j] - z;
                a[i+j] += z;
            }
        }
    }
}

template<const int mod>
vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};

    vector<ll> res(a.size() + b.size() - 1);

    int n = 1;
    while (n < (int)res.size()) n <<= 1;

    int cut = int(sqrt(mod));

    vector<CD> L(n), R(n), outs(n), outl(n);

    for (int i = 0; i < (int)a.size(); i++) {
        L[i] = CD((int)a[i] / cut, (int)a[i] % cut);
    }

    for (int i = 0; i < (int)b.size(); i++) {
        R[i] = CD((int)b[i] / cut, (int)b[i] % cut);
    }

    fft(L);
    fft(R);

    const CD I(0, 1);

    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);

        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / I;
    }

    fft(outl);
    fft(outs);

    for (int i = 0; i < (int)res.size(); i++) {
        ll av = (ll)(real(outl[i]) + 0.5) % mod;
        ll bv = (ll)(imag(outl[i]) + 0.5) + (ll)(real(outs[i]) + 0.5);
        ll cv = (ll)(imag(outs[i]) + 0.5);

        res[i] = ((av * cut + bv) % mod * cut + cv) % mod;
    }

    return res;
}

int main() {
    const int MOD = 1e9 + 7;

    vector<ll> a = {1, 2, 3};
    vector<ll> b = {4, 5};

    vector<ll> c = convMod<MOD>(a, b);

    for (ll x : c) cout << x << " ";
    cout << endl;

    return 0;
}