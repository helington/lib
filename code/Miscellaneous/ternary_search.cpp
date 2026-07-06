#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

const int INF = 1e9;

double f(double mid) {
    // função unimodal aqui
}

void solve(){
    int inter=100;
    double l = 0, r = INF;
    while(inter--){
        double m1 = l + (r-l) / 3;
        double m2 = r - (r-l) / 3;
        if(f(m1) < f(m2)) r = m2;
        else l = m1;
    }
}