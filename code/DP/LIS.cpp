#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

int LIS(const vector<int>& a){
	vector<int> lis;
	
	for(auto x : a){
		auto it = lower_bound(lis.begin(), lis.end(), x);
		if(it == lis.end()) lis.push_back(x);
		else *it = x;
	}
	return (int) lis.size();
}