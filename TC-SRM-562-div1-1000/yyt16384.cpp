#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

static int powermod(int x, int y, int m)
{
    int s = 1;
    while (y) {
        if (y & 1) {
            s = (long long)s * x % m;
        }
        x = (long long)x * x % m;
        y >>= 1;
    }
    return s;
}

class TreeGraph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> fa;
    std::vector<int> dep;
    std::vector<int> order;
    std::vector<int> size;

    TreeGraph() { }
    TreeGraph(int n_) : n(n_), edge(n), fa(n, -1), dep(n), size(n) { }

    void addEdge(int x, int y);
    void BFS(int s);
    void initSizes();
    int LCA(int x, int y) const;
    int godep(int x, int d) const;
};

void TreeGraph::addEdge(int x, int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}

void TreeGraph::BFS(int s)
{
    std::queue<int> que;
    que.push(s);
    fa[s] = -1;
    dep[s] = 0;
    order.reserve(n);
    order.clear();
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        order.push_back(x);
        for (auto y : edge[x]) {
            if (y != fa[x]) {
                fa[y] = x;
                dep[y] = dep[x] + 1;
                que.push(y);
            }
        }
    }
}

void TreeGraph::initSizes()
{
    std::fill(size.begin(), size.end(), 1);
    for (int i = n - 1; i >= 1; i--) {
        int x = order[i];
        size[fa[x]] += size[x];
    }
}

int TreeGraph::LCA(int x, int y) const
{
    if (dep[x] < dep[y]) {
        std::swap(x, y);
    }
    while (dep[x] > dep[y]) {
        x = fa[x];
    }
    while (x != y) {
        x = fa[x];
        y = fa[y];
    }
    return x;
}

int TreeGraph::godep(int x, int d) const
{
    while (dep[x] > d) {
        x = fa[x];
    }
    return x;
}

class InducedSubgraphs {
  public:
    int getCount(std::vector<int> edge1, std::vector<int> edge2, int k);

  private:
    static const int MOD = 1000000009;

    std::vector<int> fac;
    std::vector<int> faci;

    void initFactorial(int n);
    int binomial(int x, int y);
    std::pair<std::vector<int>, std::vector<int>> workSubtree(const TreeGraph &g);
    int getCount1(const TreeGraph &g, int k);
    int getCount2(const TreeGraph &g, int k);
};

int InducedSubgraphs::getCount(std::vector<int> edge1, std::vector<int> edge2, int k)
{
    int n = edge1.size() + 1;
    initFactorial(n);
    if (k == 1) {
        return fac[n];
    }
    TreeGraph g(n);
    for (int i = 0; i < n - 1; i++) {
        g.addEdge(edge1[i], edge2[i]);
    }
    g.BFS(0);
    g.initSizes();
    if (2 * k > n) {
        return getCount1(g, k);
    } else {
        return getCount2(g, k);
    }
}

void InducedSubgraphs::initFactorial(int n)
{
    fac.resize(n + 1);
    faci.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (long long)fac[i - 1] * i % MOD;
    }
    faci[n] = powermod(fac[n], MOD - 2, MOD);
    for (int i = n; i >= 1; i--) {
        faci[i - 1] = (long long)faci[i] * i % MOD;
    }
}

int InducedSubgraphs::binomial(int x, int y)
{
    return (long long)fac[x] * faci[y] % MOD * faci[x - y] % MOD;
}

std::pair<std::vector<int>, std::vector<int>> InducedSubgraphs::workSubtree(const TreeGraph &g)
{
    // fdown[i] = number of ways to permute nodes in subtree i
    // topologically
    std::vector<int> fdown(g.n);
    for (int i = g.n - 1; i >= 0; i--) {
        int x = g.order[i];
        fdown[x] = 1;
        int cursize = 0;
        for (auto y : g.edge[x]) {
            if (y != g.fa[x]) {
                int ss = binomial(cursize + g.size[y], g.size[y]);
                fdown[x] = (long long)fdown[x] * fdown[y] % MOD * ss % MOD;
                cursize += g.size[y];
            }
        }
    }
    // fup[i] = number of ways to permute nodes outside of subtree i
    // topologically
    std::vector<int> fup(g.n);
    fup[g.order[0]] = 1;
    for (int i = 1; i < g.n; i++) {
        int x = g.order[i];
        fup[x] = fup[g.fa[x]];
        int cursize = g.n - g.size[g.fa[x]];
        for (auto y : g.edge[g.fa[x]]) {
            if (y != g.fa[g.fa[x]] && y != x) {
                int ss = binomial(cursize + g.size[y], g.size[y]);
                fup[x] = (long long)fup[x] * fdown[y] % MOD * ss % MOD;
                cursize += g.size[y];
            }
        }
    }
    return std::make_pair(fdown, fup);
}

int InducedSubgraphs::getCount1(const TreeGraph &g, int k)
{
    auto fs = workSubtree(g);
    const std::vector<int> &fdown = fs.first;
    const std::vector<int> &fup = fs.second;
    // f[i][j][k] = number of ways to choose starting subtrees with
    // total size j and ending subtrees with total size k in subtree i
    std::vector<std::vector<std::vector<int>>> h(g.n, std::vector<std::vector<int>>(g.n - k + 1, std::vector<int>(g.n - k + 1)));
    for (int i = g.n - 1; i >= 0; i--) {
        int x = g.order[i];
        h[x][0][0] = 1;
        int cursize = 0;
        for (auto y : g.edge[x]) {
            if (y != g.fa[x]) {
                std::vector<std::vector<int>> hx(g.n - k + 1, std::vector<int>(g.n - k + 1));
                // Merge subtree y into current subtree
                for (int j = 0; j <= g.n - k && j <= cursize; j++) {
                    for (int p = 0; p <= g.n - k && p + j <= cursize; p++) {
                        if (j + g.size[y] <= g.n - k) {
                            int ss = binomial(j + g.size[y], g.size[y]);
                            hx[j + g.size[y]][p] = (hx[j + g.size[y]][p] + (long long)h[x][j][p] * fdown[y] % MOD * ss) % MOD;
                        }
                        if (p + g.size[y] <= g.n - k) {
                            int ss = binomial(p + g.size[y], g.size[y]);
                            hx[j][p + g.size[y]] = (hx[j][p + g.size[y]] + (long long)h[x][j][p] * fdown[y] % MOD * ss) % MOD;
                        }
                        for (int q = 0; q + j <= g.n - k && q <= g.size[y]; q++) {
                            for (int r = 0; r + p <= g.n - k && r + q <= g.size[y]; r++) {
                                int ss = (long long)binomial(j + q, q) * binomial(p + r, r) % MOD;
                                hx[j + q][p + r] = (hx[j + q][p + r] + (long long)h[x][j][p] * h[y][q][r] % MOD * ss) % MOD;
                            }
                        }
                    }
                }
                h[x] = std::move(hx);
                cursize += g.size[y];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < g.n; i++) {
        int remsz = g.n - g.size[i];
        if (remsz <= g.n - k) {
            int ss = binomial(g.n - k, remsz);
            ans = (ans + (long long)h[i][g.n - k][g.n - k - remsz] * fup[i] % MOD * ss) % MOD;
            if (remsz) {
                ans = (ans + (long long)h[i][g.n - k - remsz][g.n - k] * fup[i] % MOD * ss) % MOD;
            }
        }
    }
    // The 2*k-n nodes in the middle can be permuted arbitrarily
    ans = (long long)ans * fac[2 * k - g.n] % MOD;
    return ans;
}

int InducedSubgraphs::getCount2(const TreeGraph &g, int k)
{
    auto fs = workSubtree(g);
    const std::vector<int> &fdown = fs.first;
    const std::vector<int> &fup = fs.second;
    int ans = 0;
    // Enumerate the kth and (n-k+1)th node
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            int lca = g.LCA(i, j);
            if (g.dep[i] + g.dep[j] - 2 * g.dep[lca] != g.n - 2 * k + 1) {
                continue;
            }
            if ((lca == i ? g.n - g.size[g.godep(j, g.dep[i] + 1)] : g.size[i]) != k) {
                continue;
            }
            if ((lca == j ? g.n - g.size[g.godep(i, g.dep[j] + 1)] : g.size[j]) != k) {
                continue;
            }
            int u = lca == i ? fup[g.godep(j, g.dep[i] + 1)] : fdown[i];
            int v = lca == j ? fup[g.godep(i, g.dep[j] + 1)] : fdown[j];
            ans = (ans + (long long)u * v) % MOD;
        }
    }
    return ans;
}
