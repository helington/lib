#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

// MinCostMaxFlow
//
// min_cost_flow(s, t, f) computa o par (fluxo, custo)
// com max(fluxo) <= f que tenha min(custo)
// min_cost_flow(s, t) -> Fluxo maximo de custo minimo de s pra t
// Se for um dag, da pra substituir o SPFA por uma DP pra nao
// pagar O(nm) no comeco
// Se nao tiver aresta com custo negativo, nao precisa do SPFA
//
// O(nm + f * m log n)


const int INF = 1e9;

template<typename T>
struct MCMF {
    struct Edge {
        int to, rev, flow, cap;
        bool res;
        T cost;
        Edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}

        Edge(int to, int rev, int flow, int cap, T cost, bool res) :
            to(to), rev(rev), flow(flow), cap(cap), res(res), cost(cost) {}
    };

    vector<vector<Edge>> g;
    vector<int> par_idx, par;
    T inf;
    vector<T> dist;

    MCMF(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<T>::max()/3) {}

    void add(int u, int v, int w, T cost) {
        Edge a = Edge(v, g[v].size(), 0, w, cost, false);
        Edge b = Edge(u, g[u].size(), 0, 0, -cost, true);

        g[u].push_back(a);
        g[v].push_back(b);
    }

    vector<T> dp(int s) {
        int n = g.size();

        vector<int> indeg(n);
        for (int u = 0; u < n; u++)
            for (auto &e : g[u])
                if (e.flow < e.cap)
                    indeg[e.to]++;

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0)
                q.push(i);

        vector<int> topo;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);

            for (auto &e : g[u]) {
                if (e.flow < e.cap) {
                    if (--indeg[e.to] == 0)
                        q.push(e.to);
                }
            }
        }

        vector<T> dist(n, inf);
        dist[s] = 0;

        for (int u : topo) {
            if (dist[u] == inf) continue;
            
            for (auto &e : g[u]) {
                if (e.flow < e.cap) {
                    dist[e.to] = min(dist[e.to], dist[u] + e.cost);
                }
            }
        }

        return dist;
    }

    vector<T> spfa(int s) { // nao precisa se nao tiver custo negativo
		deque<int> q;
		vector<bool> is_inside(g.size(), 0);
		dist = vector<T>(g.size(), inf);

		dist[s] = 0;
		q.push_back(s);
		is_inside[s] = true;

		while (!q.empty()) {
			int v = q.front();
			q.pop_front();
			is_inside[v] = false;

			for (int i = 0; i < g[v].size(); i++) {
				auto [to, rev, flow, cap, res, cost] = g[v][i];
				if (flow < cap and dist[v] + cost < dist[to]) {
					dist[to] = dist[v] + cost;

					if (is_inside[to]) continue;
					if (!q.empty() and dist[to] > dist[q.front()]) q.push_back(to);
					else q.push_front(to);
					is_inside[to] = true;
				}
			}
		}
		return dist;
	}

    bool dijkstra(int s, int t, vector<T>& pot) {
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
        dist = vector<T>(g.size(), inf);
        dist[s] = 0;
        q.emplace(0, s);
        while (q.size()) {
            auto [d, v] = q.top(); q.pop();
            if (d > dist[v]) continue;
            for (int i = 0; i < g[v].size(); i++) {
                auto [to, rev, flow, cap, res, cost] = g[v][i];
                cost += pot[v] - pot[to];
                if (flow < cap and dist[v] + cost < dist[to]) {
                    dist[to] = dist[v] + cost;
                    q.emplace(dist[to], to);
                    par_idx[to] = i, par[to] = v;
                }
            }
        }

        return dist[t] < inf;
    }

    pair<int, T> min_cost_flow(int s, int t, int flow = INF) {
        vector<T> pot(g.size(), 0);

        pot = spfa(s); // usar se o grafo não for um DAG
        pot = dp(s); // usar se o grafo for um DAG

        int f = 0;
        T ret = 0;
        while (f < flow and dijkstra(s, t, pot)) {
            for (int i = 0; i < g.size(); i++) {
                if (dist[i] < inf) pot[i] += dist[i];
            }

            int mn_flow = flow - f, u = t;
            while (u != s) {
                mn_flow = min(mn_flow,
                    g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
                u = par[u];
            }

            ret += pot[t] * mn_flow;

            u = t;
            while (u != s) {
                g[par[u]][par_idx[u]].flow += mn_flow;
                g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
                u = par[u];
            }

            f += mn_flow;
        }
        
        return {f, ret};
    }

    // Opcional: retorna as arestas originais por onde passa flow = cap
	vector<pair<int,int>> recover() {
		vector<pair<int,int>> used;
		for (int i = 0; i < g.size(); i++) for (edge e : g[i])
			if(e.flow == e.cap && !e.res) used.push_back({i, e.to});
		return used;
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, c; cin >> m >> n >> c;
    int s=0, t=n+1;
    MCMF<ll> mcmf(n+2);
    for (int i = 0; i <= n; i++)
        mcmf.add(i, i+1, c, 0);

    while (m--) {
        int u, v, p; cin >> u >> v >> p;
        mcmf.add(u, v, 1, -p);
    }

    auto ans = mcmf.min_cost_flow(s, t);

    cout << -ans.second << endl;

    return 0;
}