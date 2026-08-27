#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define ld long double
#define int ll
using pii = pair<int,int>;
using vi = vector<int>;

using namespace std;

struct Angle {
	int x, y;
	int t;
	Angle(int x, int y, int t=0) : x(x), y(y), t(t) {}
	Angle operator-(Angle b) const { return {x-b.x, y-b.y, t}; }
	int half() const {
		assert(x || y);
		return y < 0 || (y == 0 && x < 0);
	}
	Angle t90() const  { return {-y, x, t + (half() && x >= 0)}; }
	Angle t180() const { return {-x, -y, t + half()}; }
	Angle t360() const { return {x, y, t + 1}; }
};

bool operator<(Angle a, Angle b) {
	return make_tuple(a.t, a.half(), a.y * b.x) <
	       make_tuple(b.t, b.half(), a.x * b.y);
}

pii operator+(pii a, pii b) {
	return pii(a.first + b.first, a.second + b.second);
}
pii operator-(pii a, pii b) {
	return pii(a.first - b.first, a.second - b.second);
}


ld andle(int x, int y){
    return atan2(y, x);
}

const ld PI = acos(-1);

signed main(){
    ios::sync_with_stdio(0), cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<pii> sla;
    vector<pair<ld, int>> sortado;

    for(int i=0, a, b, c, d; i<n; i++){
        cin >> a >> b >> c >> d;
        pair at(a-b, c-d);
        sla.push_back(at);
        
        ld ang = andle(at.first, at.second);

        sortado.push_back({ang, i});
        sortado.push_back({ang+(PI+PI), i});
        sortado.push_back({ang-(PI+PI), i});
    }

    sort(begin(sortado), end(sortado));

    vector<pii> ps;
    ps.push_back({0, 0});

    for(auto [a, i] : sortado){
        ps.push_back(ps.back() + sla[i]);
    }

    auto solve = [&](int x, int y){

        ld ang = andle(x, y);
        ld l = ang - PI/2.0;
        ld r = ang + PI/2.0;

        int L = lower_bound(begin(sortado), end(sortado), pair<ld, int>(l, -1)) - begin(sortado); // priemeiro que ta
        int R = upper_bound(begin(sortado), end(sortado), pair<ld, int>(r, -1)) - begin(sortado); //primeiro que não ta

        pii sum = ps[R] - ps[L];

        return sum.first*x + sum.second*y;
    };

    while(q--){
        int x, y; cin >> x >> y;
        int ans = 0;

        for(int i=-1; i<=1; i+=2)
            for(int j=-1; j<=1; j+=2)
                ans = max(ans, solve(x*i, y*j));

        cout << ans << "\n";
    }

}