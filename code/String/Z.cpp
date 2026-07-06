#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

vector<int> Z(string p){
  int n=  p.size();
  vector<int> z(n,0);
  int l=0, r=0;
  for(int i=1;i<n;i++){
    if(i<=r){
      int k = i-l;
      z[i] = min(r-i+1, z[k]);
    }
     
    while(i + z[i]<n && p[z[i]]==p[i+z[i]]){
      z[i]++;
    }
    if(i + z[i]-1>r){
      l=i;
      r = i+ z[i]-1;
    }
    
  }
  return z;
}