#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define ld long double
const ll mod = 1e9+7;

ll merge(vector<int> &v, ll l, ll r,ll mid){
  ll inversions = 0;
  vector<int> order;
  ll i = l; ll j =mid+1;
  while(i<=mid  && j<=r){
    if(v[i]<=v[j]){
      order.push_back(v[i]);
      i++;
    }
    else{
      order.push_back(v[j]);
      inversions+=(mid-i+1);
      j++;
    }
  }
  
  while(i<=mid){order.push_back(v[i++]);}
  while(j<=r){order.push_back(v[j++]);}
  
  int n = order.size();
  int k =l;
  for(int i=0;i<n;i++){
    v[k] = order[i];
    k++;
  }
  return inversions;
  
}
ll merge_sort(vector<int> &v, ll l ,ll r){
  if(l>=r) return 0;
  ll mid = (r+l)/2;
  return merge_sort(v,l,mid)+merge_sort(v,mid+1,r)+merge(v,l,r,mid);
}
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int tc;cin>>tc;while(tc--){
        ll n; cin>>n;
      
        vector<int> v(n); for(auto &x:v) {cin>>x;}
      
        ll inversions = merge_sort(v,0,n-1);
        cout<<inversions<<endl;
    }
}