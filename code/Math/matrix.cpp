#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
using vi = vector<int>;
using pii = pair<int, int>;

template<typename T>
struct Matrix : vector<vector<T>> {
    int n, m;

    Matrix(int n, int m, bool ident = false) :
        vector<vector<T>>(n, vector<T>(m, 0)), n(n), m(m) {
            if (ident) {
                for (int i = 0; i < n; i++) (*this)[i][i] = 1;
            }
        }
    
    Matrix(const vector<vector<T>> &c) :
        vector<vector<T>>(c), n(c.size()), m(c[0].size()) {}

    Matrix<T> operator * (const Matrix<T> &r) {
        Matrix<T> res(n, r.m);

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if ((*this)[i][k] == 0) continue;

                for (int j = 0; j < r.m; j++) {
                    res[i][j] = mod_add(
                        res[i][j],
                        mod_mul((*this)[i][k], r[k][j])
                    );
                }
            }
        }

        return res;
    }

    Matrix<T> fexp(T e) {
        Matrix<T> res(n, n, true), base = *this;

        while(e) {
            if (e&1) res = res * base;
            e >>= 1;
            base = base * base;
        }

        return res;
    }

    friend ostream &operator << (ostream &os, const Matrix<T> &mat) {
        for (int i = 0; i < mat.n; i++) {
            for (int j = 0; j < mat.m; j++) os << mat[i][j] << " ";
            os << endl;
        }

        return os;
    }
};