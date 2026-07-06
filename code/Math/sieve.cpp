#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

const int MAXN = 2e5 + 5;

bool is_prime[MAXN];

vector<int> sieve() {
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j <= MAXN; j += i)
                is_prime[j] = false;
        }
    }

    return primes;
}

int spf[MAXN];

void sieve() {
    spf[0] = spf[1] = 0;

    for (int i = 2; i <= MAXN; i++) {
        if (!spf[i]) {
            spf[i] = i;
            for (int j = 2 * i; j <= MAXN; j += i)
                if (!spf[j])
                    spf[j] = i;
        }
    }

    return spf;
}

ll sumDivisors[MAXN];

void sieve() {
    for (int i = 1; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            sumDivisors[j] += i;
        }
    }
}

ll numDivisors[MAXN];

void sieve() {
    for (int i = 1; i < MAXN; i++) {
        for (int j = i; j < MAXN; j += i) {
            numDivisors[j]++;
        }
    }
}