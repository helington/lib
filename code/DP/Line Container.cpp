// Line Container: Dynamic Convex Hull Trick for Maximum
// Time: Insert/Query O(log N) | Space: O(N)
// Note: Computes Max(ax + b) | Change < to > in Line Operator for Min
struct line {
    mutable int a, b, i;

    bool operator<(const line &o) const {
        return tie(a, b) < tie(o.a, o.b);
    }

    bool operator<(const int x) const {
        return i < x;
    }
};

struct line_container : multiset<line, less<>> {
    const int inf = 1e18;

    int div(int x, int y) {
        return (x / y) - (((x ^ y) < 0) and x % y);
    }

    bool isect(iterator s, iterator t) {
        if (t == end()) return s->i = inf, false;
        if (s->a == t->a) s->i = -inf;
        else s->i = div(t->b - s->b, s->a - t->a);
        return s->i >= t->i;
    }

    void insert(int a, int b) {
        auto z = multiset::insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() and isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() and (--x)->i >= y->i) isect(x, erase(y));
    }

    int max(int x) {
        auto l = lower_bound(x);
        return l->a * x + l->b;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    line_container cht;//    cuidado ao pesquisar max, verficiar se cht.empty()

    // adiciona retas y = ax + b
    cht.insert(2, 3);    // y = 2x + 3
    cht.insert(-1, 10);  // y = -x + 10
    cht.insert(5, -7);   // y = 5x - 7

    cout << cht.max(0) << endl;  // max(3, 10, -7) = 10
    cout << cht.max(2) << endl;  // max(7, 8, 3) = 8
    cout << cht.max(5) << endl;  // max(13, 5, 18) = 18

    return 0;
}