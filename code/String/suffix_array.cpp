#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

vector<int> suffix_array(string s){ 
    int n = (s += "!").size();//if vector, s.push_back(-INF);
    vector<int> sf(n), ord(n), aux(n), cnt(n);
    iota(begin(sf), end(sf), 0);
    sort(begin(sf), end(sf), [&](int i, int j){ return s[i] < s[j]; });

    int cur = ord[sf[0]] = 0;
    for(int i=1; i<n; i++) 
        ord[sf[i]] = s[sf[i]] == s[sf[i-1]] ? cur : ++cur;
        
    for(int k=1; cur+1 < n && k < n; k<<=1){
        cnt.assign(n, 0);
        for(auto &i : sf)         i = (i-k+n)%n, cnt[ord[i]]++;
        for(int i=1; i<n; i++)    cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; i--) aux[--cnt[ord[sf[i]]]] = sf[i];
        sf.swap(aux);

        aux[sf[0]] = cur = 0;
        for(int i=1; i<n; i++)
            aux[sf[i]] = ord[sf[i]] == ord[sf[i-1]] && 
            ord[(sf[i]+k)%n] == ord[(sf[i-1]+k)%n] ? cur : ++cur;
        ord.swap(aux);
    }
    return vector<int>(begin(sf)+1, end(sf));
}

vector<int> LCP(string &s, vector<int> &sf){ 
    int n = s.size();
    vector<int> lcp(n), pof(n);
    for(int i=0; i<n; i++) pof[sf[i]] = i;

    for(int i=0, j, k=0; i<n; k?--k:k, i++){
        if(!pof[i]) continue; 
        j = sf[pof[i]-1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[pof[i]] = k;
    }
    return lcp;
}