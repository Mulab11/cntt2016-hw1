#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

static const int INF = 0x3f3f3f3f;

class TreeGraph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> fa;
    std::vector<int> order;

    TreeGraph() { }
    TreeGraph(int n_) : n(n_), edge(n), fa(n, -1) { }

    void addEdge(int x, int y);
    void BFS(int s);
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
    order.reserve(n);
    order.clear();
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        order.push_back(x);
        for (auto y : edge[x]) {
            if (y != fa[x]) {
                fa[y] = x;
                que.push(y);
            }
        }
    }
}

class FlowGraph {
  public:
    int n = 0;
    int s = -1;
    int t = -1;
    std::vector<std::vector<std::tuple<int, int, int, int>>> edge;

    FlowGraph() { }
    FlowGraph(int n_, int s_, int t_) : n(n_), s(s_), t(t_), edge(n) { }

    void addEdge(int x, int y, int w, int c);
    int minCostFlow();

  private:
    std::vector<int> dist;
    std::vector<int> pre;

    void getDist();
    int augment();
};

void FlowGraph::addEdge(int x, int y, int w, int c)
{
    int idx = edge[x].size();
    int idy = edge[y].size();
    edge[x].push_back(std::make_tuple(y, w, c, idy));
    edge[y].push_back(std::make_tuple(x, 0, -c, idx));
}

int FlowGraph::minCostFlow()
{
    dist.resize(n);
    pre.resize(n);
    int cost = 0;
    while (true) {
        getDist();
        if (dist[t] >= 0) {
            break;
        }
        cost += augment();
    }
    return cost;
}

void FlowGraph::getDist()
{
    std::queue<int> que;
    std::vector<char> inque(n);
    que.push(s);
    inque[s] = true;
    std::fill(dist.begin(), dist.end(), INF);
    dist[s] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        inque[x] = false;
        for (auto e : edge[x]) {
            int y = std::get<0>(e);
            int c = std::get<2>(e);
            if (std::get<1>(e) && dist[x] + c < dist[y]) {
                dist[y] = dist[x] + c;
                pre[y] = std::get<3>(e);
                if (!inque[y]) {
                    que.push(y);
                    inque[y] = true;
                }
            }
        }
    }
}

int FlowGraph::augment()
{
    int flow = INF;
    int x = t;
    while (x != s) {
        auto e = edge[x][pre[x]];
        int y = std::get<0>(e);
        flow = std::min(flow, std::get<1>(edge[y][std::get<3>(e)]));
        x = y;
    }
    x = t;
    while (x != s) {
        auto &e = edge[x][pre[x]];
        int y = std::get<0>(e);
        std::get<1>(edge[y][std::get<3>(e)]) -= flow;
        std::get<1>(e) += flow;
        x = y;
    }
    return flow * dist[t];
}

class DeerInZooDivOne {
  public:
    int getmax(std::vector<int> a, std::vector<int> b);

  private:
    int getmaxTwoTrees(TreeGraph g1, TreeGraph g2, int root1);
};

int DeerInZooDivOne::getmax(std::vector<int> a, std::vector<int> b)
{
    int n = a.size() + 1;
    TreeGraph g(n);
    for (int i = 0; i < n - 1; i++) {
        g.addEdge(a[i], b[i]);
    }
    g.BFS(0);
    int ans = 0;
    // Enumerate an edge between two trees
    for (int i = 1; i < n; i++) {
        std::vector<char> insubtr(n);
        for (int j = 0; j < n; j++) {
            int u = j;
            while (u != -1 && u != i) {
                u = g.fa[u];
            }
            if (u == i) {
                insubtr[j] = true;
            }
        }
        std::vector<int> id(n);
        int g1n = 0;
        int g2n = 0;
        for (int j = 0; j < n; j++) {
            if (insubtr[j]) {
                id[j] = g1n++;
            } else {
                id[j] = g2n++;
            }
        }
        TreeGraph g1(g1n);
        TreeGraph g2(g2n);
        for (int j = 1; j < n; j++) {
            if (j != i) {
                if (insubtr[j]) {
                    g1.addEdge(id[j], id[g.fa[j]]);
                } else {
                    g2.addEdge(id[j], id[g.fa[j]]);
                }
            }
        }
        // Assume one of the endpoints is chosen
        ans = std::max(ans, getmaxTwoTrees(g1, g2, id[i]));
        ans = std::max(ans, getmaxTwoTrees(g2, g1, id[g.fa[i]]));
    }
    return ans;
}

int DeerInZooDivOne::getmaxTwoTrees(TreeGraph g1, TreeGraph g2, int root1)
{
    g1.BFS(root1);
    g2.BFS(0);
    std::vector<std::vector<int>> trans(3 * g2.n);
    for (int i = 0; i < g2.n; i++) {
        for (auto y : g2.edge[i]) {
            if (y != g2.fa[i]) {
                trans[i].push_back(y);
            }
        }
    }
    for (int i = 1; i < g2.n; i++) {
        for (auto y : g2.edge[g2.fa[i]]) {
            if (y != g2.fa[g2.fa[i]] && y != i) {
                trans[i + g2.n].push_back(y);
            }
        }
        if (g2.fa[i]) {
            trans[i + g2.n].push_back(g2.fa[i] + g2.n);
        }
    }
    for (int i = 0; i < g2.n; i++) {
        for (auto y : g2.edge[i]) {
            if (y != g2.fa[i]) {
                trans[i + 2 * g2.n].push_back(y);
            }
        }
        if (i) {
            trans[i + 2 * g2.n].push_back(i + g2.n);
        }
    }
    // f[i][j] = answer with subtree i and subtree j
    // f[i][j + n] = answer with subtree i and anything other than
    // subtree j (rooted at fa[j])
    // f[i][j + 2 * n] = answer with subtree i and whole g2 (rooted at
    // j)
    std::vector<std::vector<int>> f(g1.n, std::vector<int>(3 * g2.n));
    for (int i = g1.n - 1; i >= 0; i--) {
        int x = g1.order[i];
        std::vector<int> s1;
        for (auto y : g1.edge[x]) {
            if (y != g1.fa[x]) {
                s1.push_back(y);
            }
        }
        for (int j = 0; j < 3 * g2.n; j++) {
            int nl = s1.size();
            int nr = trans[j].size();
            FlowGraph gf(nl + nr + 2, nl + nr, nl + nr + 1);
            for (int k = 0; k < nl; k++) {
                gf.addEdge(gf.s, k, 1, 0);
            }
            for (int k = 0; k < nr; k++) {
                gf.addEdge(k + nl, gf.t, 1, 0);
            }
            for (int k = 0; k < nl; k++) {
                for (int p = 0; p < nr; p++) {
                    gf.addEdge(k, p + nl, 1, -f[s1[k]][trans[j][p]]);
                }
            }
            f[x][j] = std::max(f[x][j], -gf.minCostFlow() + 1);
        }
    }
    int ans = 0;
    for (int i = 0; i < g2.n; i++) {
        ans = std::max(ans, f[g1.order[0]][i + 2 * g2.n]);
    }
    return ans;
}
