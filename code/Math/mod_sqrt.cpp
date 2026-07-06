ll mod_sqrt(ll a) {
    a %= MOD;
    if (a < 0) a += MOD;

    if (a == 0) return 0;

    if (fexp(a, (MOD - 1) / 2) != 1) return -1;

    if (MOD % 4 == 3) {
        return fexp(a, (MOD + 1) / 4);
    }

    ll s = MOD - 1;
    int r = 0;

    while (s % 2 == 0) {
        s /= 2;
        r++;
    }

    ll n = 2;
    while (fexp(n, (MOD - 1) / 2) != MOD - 1) {
        n++;
    }

    ll x = fexp(a, (s + 1) / 2);
    ll b = fexp(a, s);
    ll g = fexp(n, s);

    while (true) {
        ll t = b;
        int m = 0;

        while (m < r && t != 1) {
            t = mod_mul(t, t);
            m++;
        }

        if (m == 0) return x;

        ll gs = fexp(g, 1LL << (r - m - 1));

        g = mod_mul(gs, gs);
        x = mod_mul(x, gs);
        b = mod_mul(b, g);
        r = m;
    }
}