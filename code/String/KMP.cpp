// Pi Array (Prefix Function for KMP)

// p[i] stores the length of the longest proper prefix of the substring s[0...i] 
// that is also a suffix of this substring.
//
// Time Complexity: O(N)
// Space Complexity: O(N)


// To use kmp, we only need to find prefix function of both the pattern and the text. Then we can find all the occurrences of the pattern in the text in O(N) time complexity.
vector<int> Pi(const string &s) {
    int n = (int) s.size();
    vector<int> p(n, 0);

    for (int i = 1, j = 0; i < n; i++) {
        while(j > 0 and s[j] != s[i]) j = p[j-1];
        if (s[j] == s[i]) j++;
        p[i] = j;
    }

    return p;
}

// Automaton for KMP
vector<vector<int>> automato(string s){
    s+='#';
    vector<int> pi =  Pi(s);
    int n = s.size();
    vector<vector<int>> aut(n,vector<int>(26,0));
    for(int i=0;i<n;i++){
    for(int c=0;c<26;c++){
        if (i > 0 && 'a' + c != s[i])
            aut[i][c] = aut[pi[i-1]][c];
        else
            aut[i][c] = i + ('a' + c == s[i]);
    }
    }

    return aut;
}