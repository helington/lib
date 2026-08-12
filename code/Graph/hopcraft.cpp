struct HopcroftKarp {
  static const int inf = 1e9;
  int n;
  vector<int> l, r, d;
  vector<vector<int>> g;
  HopcroftKarp(int _n, int _m) {
    n = _n;
    int p = _n + _m + 1;
    g.resize(p);
    l.resize(p, 0);
    r.resize(p, 0);
    d.resize(p, 0);
  }
  void add_edge(int u, int v) {
    g[u].push_back(v + n); //right id is increased by n, so is l[u]
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (!l[u]) d[u] = 0, q.push(u);
      else d[u] = inf;
    }
    d[0] = inf;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : g[u]) {
        if (d[r[v]] == inf) {
          d[r[v]] = d[u] + 1;
          q.push(r[v]);
        }
      }
    }
    return d[0] != inf;
  }




// Algorithm: Hopcroft-Karp, Encontra o maior matching em um grafo bipartido. Big o(E * V^0.5)
// Usar 1-Based indexing; Na main trate como os vertices da esquerda de 1 a n e os da direita de 1 a m. A função add_edge(u, v) adiciona uma aresta entre u e v, onde u é um vértice da esquerda e v é um vértice da direita. A função max_matching() retorna o tamanho do maior matching encontrado.
// o vector L[u] armazeda com que vértice da direita o vértice u da esquerda está emparelhado, e o vector R[v] armazena com que vértice da esquerda o vértice v da direita está emparelhado. Se L[u] = 0, então u não está emparelhado, e se R[v] = 0, então v não está emparelhado.
  