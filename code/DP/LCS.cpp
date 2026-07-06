#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

int lcs(const string& s1, const string& s2) {
    int n = s1.size();
    int m = s2.size();

    int dp[n+1][m+1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[n][m];
}

// Reconstruct the String (Backtracking)
string reconstruct(const vector<vector<int>>& dp, string& s1, string& s2) {
    string res = "";
    int i = s1.size(), j = s2.size();
    
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            res += s1[i - 1];
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    reverse(res.begin(), res.end());
    return res;
}