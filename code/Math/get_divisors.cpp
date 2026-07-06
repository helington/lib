#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

vector<ll> getdivisors(ll n) {
    vector<ll> divisors;

    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n/i) divisors.push_back(n / i);
        }
    }

    sort(divisors.begin(), divisors.end());
    return divisors;
}

vector<pair<ll, int>> getprimes(ll n) {
    vector<pair<ll, int>> primes;

    for (ll i = 2; i * i <= n; i++) {
        int cnt = 0;

        while (n % i == 0) {
            n /= i;
            cnt++;
        }

        if (cnt > 0) primes.push_back({i, cnt});
    }

    if (n > 1) primes.push_back({n, 1});
    
    return primes;
}