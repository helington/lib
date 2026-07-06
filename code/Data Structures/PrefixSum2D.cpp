#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    int n,m; cin>>n>>m;
    vector<vector<ll>> v(n,vector<ll>(m,0));
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>v[i][j];

    vector<vector<ll>> prefix(n+1,vector<ll>(m+1,0));

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) {
            prefix[i][j] = prefix[i-1][j]+prefix[i][j-1]+v[i-1][j-1] - prefix[i-1][j-1];
        }
    }

    int q;cin>>q;
    while (q--){
        int a,b,c,d; cin>>a>>b>>c>>d;
        cout<<prefix[c][d]-prefix[a-1][d]-prefix[c][b-1]+prefix[a-1][b-1]<<endl;
    }
}