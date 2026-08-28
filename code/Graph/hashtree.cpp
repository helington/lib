// Tree Isomorphism Hash - collision free
// Compara subarvores enraizadas por estrutura.
//
// Uso:
// TreeHash TH;
// auto h = TH.build(adj, root);
//
// Mesma arvore:
// h[u] == h[v]  <=>  subtree(u) isomorfa a subtree(v)
//
// Arvores diferentes:
// TreeHash TH;
// auto h1 = TH.build(adj1, root1);
// auto h2 = TH.build(adj2, root2);
// h1[u] == h2[v]  <=>  subtrees isomorfas
//
// IMPORTANTE:
// Para comparar hashes de ARVORES DIFERENTES, use o MESMO objeto TreeHash.
// Os IDs sao internos ao objeto. Nao compare IDs produzidos por TreeHash distintos.
//
// A subarvore de u e definida em relacao a root passada no build:
// ela contem u e apenas seus descendentes.
// Nao representa a arvore inteira rerootada em u.
//
// Indexacao:
// Funciona naturalmente em 0-indexado.
// Para 1-indexado, use adj com tamanho n+1; o indice 0 simplesmente fica inutilizado.
//
// Complexidade:
// build: O(n log n)
// comparacao de duas subarvores: O(1)
// memoria: O(n)
//
// Ideia:
// O hash de u e um ID unico associado ao vetor ORDENADO dos hashes dos filhos.
// Como usamos map<vector<int>, int>, nao ha colisao probabilistica.

struct TreeHash {
    map<vector<int>, int> mp;

    int get(vector<int> v) {
        sort(v.begin(), v.end());

        auto it = mp.find(v);
        if (it != mp.end())
            return it->second;

        int id = mp.size();
        mp[v] = id;

        return id;
    }

    vector<int> build(const vector<vector<int>> &adj, int root) {
        int n = adj.size();

        vector<int> par(n, -1);
        vector<int> order;
        order.reserve(n);

        par[root] = root;
        order.push_back(root);

        // Monta ordem pai -> filho
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];

            for (int v : adj[u]) {
                if (v == par[u]) continue;

                par[v] = u;
                order.push_back(v);
            }
        }

        vector<int> h(n);

        // Processa de baixo para cima
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];

            vector<int> children;

            for (int v : adj[u]) {
                if (par[v] == u)
                    children.push_back(h[v]);
            }

            h[u] = get(children);
        }

        return h;
    }

    int root_hash(const vector<vector<int>> &adj, int root) {
        return build(adj, root)[root];
    }
};