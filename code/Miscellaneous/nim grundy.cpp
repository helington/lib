#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

vector<int> seen;

int timer = 1;

int mex(const vector<int>& vals) {
    for (int x : vals) {
        if (x >= 0 && x < (int)seen.size()) {
            seen[x] = timer;
        }
    }

    int ans = 0;

    while (ans < (int)seen.size() && seen[ans] == timer) {
        ans++;
    }

    timer++;

    return ans;
}


signed main(){
    int n,k;cin>>n>>k;
    seen.assign(k + 1, 0);
    vi g(n+1,0);
    g[0] = 0;
    vi move(k);
    for(int i=0;i<k;i++){
        cin>>move[i];
    }
    for(int i=1;i<=n;i++){
        vi vt;
        for(int j=0;j<k;j++){
            if(i-move[j]>=0){
                vt.push_back(g[i-move[j]]);
            }
        }
        g[i] = mex(vt);
        if(g[i]){
            cout<<"W";
        }
        else cout<<"L";
    }
    return 0;
}