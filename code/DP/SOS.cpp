#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

void SOS(vector<ll> &f, int n){
    for(int i=0;i<n;i++){
        for(int mask=0;mask<(1<<n);mask++){
            if(mask&(1<<i))f[mask] += f[mask^(1<<i)];
                
        }
    }
}