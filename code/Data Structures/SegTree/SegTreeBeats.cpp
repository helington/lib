// Segment Tree Beats
//
// Suporta em intervalo [l, r]:
//
// update_min(l,r,x): a[i] = min(a[i], x)   (CHMIN)
// update_max(l,r,x): a[i] = max(a[i], x)   (CHMAX)
// update_add(l,r,x): a[i] += x
// set_point(p,x): a[p] = x
//
//
// Também pode inicializar tudo com 0:
// STBeats st(n);
//
// Indexacao: 0-indexado, intervalos inclusivos [l,r].
// COMPLEXIDADE:
//
// build:       O(n)
// add:         O(log n)
// sum/min/max: O(log n)
// set_point:   O(log n)
//
// chmin/chmax: O(log^2 n) amortizado por operacao.
//
// Memoria: O(n)
//

struct STBeats {
    static constexpr ll INF = (1LL << 60);

    struct Node {
        ll mx = -INF, mx2 = -INF, cx = 0;
        ll mn = INF, mn2 = INF, cn = 0;
        ll sum = 0;
        ll lz_add = 0;
    };

    int n;
    vector<Node> t;

    // Inicializa com vetor
    STBeats(const vector<ll>& a)
        : n(a.size()), t(4 * max(1, (int)a.size())) {
        if (n)
            build(1, 0, n - 1, a);
    }

    // Inicializa vetor de tamanho n cheio de zeros
    STBeats(int n)
        : STBeats(vector<ll>(n, 0)) {}

    void pull(int i) {
        int l = 2 * i;
        int r = 2 * i + 1;

        t[i].sum = t[l].sum + t[r].sum;

        // Calcula maximo, segundo maximo e qtd. de maximos
        if (t[l].mx > t[r].mx) {
            t[i].mx = t[l].mx;
            t[i].cx = t[l].cx;
            t[i].mx2 = max(t[l].mx2, t[r].mx);
        }
        else if (t[l].mx < t[r].mx) {
            t[i].mx = t[r].mx;
            t[i].cx = t[r].cx;
            t[i].mx2 = max(t[l].mx, t[r].mx2);
        }
        else {
            t[i].mx = t[l].mx;
            t[i].cx = t[l].cx + t[r].cx;
            t[i].mx2 = max(t[l].mx2, t[r].mx2);
        }

        // Calcula minimo, segundo minimo e qtd. de minimos
        if (t[l].mn < t[r].mn) {
            t[i].mn = t[l].mn;
            t[i].cn = t[l].cn;
            t[i].mn2 = min(t[l].mn2, t[r].mn);
        }
        else if (t[l].mn > t[r].mn) {
            t[i].mn = t[r].mn;
            t[i].cn = t[r].cn;
            t[i].mn2 = min(t[l].mn, t[r].mn2);
        }
        else {
            t[i].mn = t[l].mn;
            t[i].cn = t[l].cn + t[r].cn;
            t[i].mn2 = min(t[l].mn2, t[r].mn2);
        }
    }

    // Soma v em todos os elementos do node
    void apply_add(int i, int l, int r, ll v) {
        t[i].sum += v * (r - l + 1);

        t[i].mx += v;
        if (t[i].mx2 != -INF)
            t[i].mx2 += v;

        t[i].mn += v;
        if (t[i].mn2 != INF)
            t[i].mn2 += v;

        t[i].lz_add += v;
    }

    // CHMIN no node:
    // troca somente os elementos iguais ao maximo por v.
    //
    // Deve ser usado apenas quando mx2 < v < mx
    // (ou quando o node tem apenas um valor).
    void apply_min(int i, ll v) {
        if (t[i].mx <= v)
            return;

        t[i].sum -= t[i].cx * (t[i].mx - v);

        // Se todos os valores eram iguais
        if (t[i].mn == t[i].mx)
            t[i].mn = v;

        // Se o maximo tambem era o segundo minimo
        else if (t[i].mn2 == t[i].mx)
            t[i].mn2 = v;

        t[i].mx = v;
    }

    // CHMAX no node:
    // troca somente os elementos iguais ao minimo por v.
    //
    // Deve ser usado apenas quando mn < v < mn2
    // (ou quando o node tem apenas um valor).
    void apply_max(int i, ll v) {
        if (t[i].mn >= v)
            return;

        t[i].sum += t[i].cn * (v - t[i].mn);

        // Se todos os valores eram iguais
        if (t[i].mx == t[i].mn)
            t[i].mx = v;

        // Se o minimo tambem era o segundo maximo
        else if (t[i].mx2 == t[i].mn)
            t[i].mx2 = v;

        t[i].mn = v;
    }

    void push(int i, int l, int r) {
        if (l == r)
            return;

        int m = (l + r) / 2;

        // ADD precisa ser propagado primeiro
        if (t[i].lz_add) {
            apply_add(2 * i, l, m, t[i].lz_add);
            apply_add(2 * i + 1, m + 1, r, t[i].lz_add);

            t[i].lz_add = 0;
        }

        // Os filhos nao podem ter maximo maior que o maximo do pai
        apply_min(2 * i, t[i].mx);
        apply_min(2 * i + 1, t[i].mx);

        // Os filhos nao podem ter minimo menor que o minimo do pai
        apply_max(2 * i, t[i].mn);
        apply_max(2 * i + 1, t[i].mn);
    }

    void build(int i, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[i] = {
                a[l], -INF, 1,
                a[l], INF, 1,
                a[l], 0
            };
            return;
        }

        int m = (l + r) / 2;

        build(2 * i, l, m, a);
        build(2 * i + 1, m + 1, r, a);

        pull(i);
    }

    // a[j] = min(a[j], x), j em [ql,qr]
    void update_min(int i, int l, int r, int ql, int qr, ll x) {
        if (r < ql || qr < l || t[i].mx <= x)
            return;

        // Somente os elementos iguais ao maximo serao alterados
        if (ql <= l && r <= qr && t[i].mx2 < x) {
            apply_min(i, x);
            return;
        }

        push(i, l, r);

        int m = (l + r) / 2;

        update_min(2 * i, l, m, ql, qr, x);
        update_min(2 * i + 1, m + 1, r, ql, qr, x);

        pull(i);
    }

    // a[j] = max(a[j], x), j em [ql,qr]
    void update_max(int i, int l, int r, int ql, int qr, ll x) {
        if (r < ql || qr < l || t[i].mn >= x)
            return;

        // Somente os elementos iguais ao minimo serao alterados
        if (ql <= l && r <= qr && t[i].mn2 > x) {
            apply_max(i, x);
            return;
        }

        push(i, l, r);

        int m = (l + r) / 2;

        update_max(2 * i, l, m, ql, qr, x);
        update_max(2 * i + 1, m + 1, r, ql, qr, x);

        pull(i);
    }

    // a[j] += v, j em [ql,qr]
    void update_add(int i, int l, int r, int ql, int qr, ll v) {
        if (r < ql || qr < l)
            return;

        if (ql <= l && r <= qr) {
            apply_add(i, l, r, v);
            return;
        }

        push(i, l, r);

        int m = (l + r) / 2;

        update_add(2 * i, l, m, ql, qr, v);
        update_add(2 * i + 1, m + 1, r, ql, qr, v);

        pull(i);
    }

    ll query_sum(int i, int l, int r, int ql, int qr) {
        if (r < ql || qr < l)
            return 0;

        if (ql <= l && r <= qr)
            return t[i].sum;

        push(i, l, r);

        int m = (l + r) / 2;

        return query_sum(2 * i, l, m, ql, qr)
             + query_sum(2 * i + 1, m + 1, r, ql, qr);
    }

    ll query_min(int i, int l, int r, int ql, int qr) {
        if (r < ql || qr < l)
            return INF;

        if (ql <= l && r <= qr)
            return t[i].mn;

        push(i, l, r);

        int m = (l + r) / 2;

        return min(
            query_min(2 * i, l, m, ql, qr),
            query_min(2 * i + 1, m + 1, r, ql, qr)
        );
    }

    ll query_max(int i, int l, int r, int ql, int qr) {
        if (r < ql || qr < l)
            return -INF;

        if (ql <= l && r <= qr)
            return t[i].mx;

        push(i, l, r);

        int m = (l + r) / 2;

        return max(
            query_max(2 * i, l, m, ql, qr),
            query_max(2 * i + 1, m + 1, r, ql, qr)
        );
    }

    // Opcional, mas muito util em prova
    void set_point(int i, int l, int r, int p, ll x) {
        if (l == r) {
            t[i] = {
                x, -INF, 1,
                x, INF, 1,
                x, 0
            };
            return;
        }

        push(i, l, r);

        int m = (l + r) / 2;

        if (p <= m)
            set_point(2 * i, l, m, p, x);
        else
            set_point(2 * i + 1, m + 1, r, p, x);

        pull(i);
    }

    // ================================================================
    // WRAPPERS
    //
    // Use estas funcoes na prova. Nao precisa passar i=1, [0,n-1].
    // ================================================================

    void update_min(int l, int r, ll x) {
        if (n && l <= r)
            update_min(1, 0, n - 1, l, r, x);
    }

    void update_max(int l, int r, ll x) {
        if (n && l <= r)
            update_max(1, 0, n - 1, l, r, x);
    }

    void update_add(int l, int r, ll x) {
        if (n && l <= r)
            update_add(1, 0, n - 1, l, r, x);
    }

    ll query_sum(int l, int r) {
        if (!n || l > r)
            return 0;

        return query_sum(1, 0, n - 1, l, r);
    }

    ll query_min(int l, int r) {
        if (!n || l > r)
            return INF;

        return query_min(1, 0, n - 1, l, r);
    }

    ll query_max(int l, int r) {
        if (!n || l > r)
            return -INF;

        return query_max(1, 0, n - 1, l, r);
    }

    void set_point(int p, ll x) {
        if (n)
            set_point(1, 0, n - 1, p, x);
    }
};