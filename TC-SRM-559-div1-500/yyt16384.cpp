#include <queue>
#include <utility>
#include <vector>

class TreeGraph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> fa;
    std::vector<int> dist;

    TreeGraph() { }
    TreeGraph(int n_) : n(n_), edge(n), fa(n, -1), dist(n) { }
    TreeGraph(int n_, const std::vector<std::pair<int, int>> &e);

    void addEdge(int x, int y);
    void BFSDist(int s);
};

TreeGraph::TreeGraph(int n_, const std::vector<std::pair<int, int>> &e) : TreeGraph(n_)
{
    for (auto x : e) {
        addEdge(x.first, x.second);
    }
}

void TreeGraph::addEdge(int x, int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}

void TreeGraph::BFSDist(int s)
{
    std::queue<int> que;
    que.push(s);
    fa[s] = -1;
    dist[s] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto y : edge[x]) {
            if (y != fa[x]) {
                fa[y] = x;
                dist[y] = dist[x] + 1;
                que.push(y);
            }
        }
    }
}

class HatRack {
  public:
    long long countWays(std::vector<int> knob1, std::vector<int> knob2);
};

long long HatRack::countWays(std::vector<int> knob1, std::vector<int> knob2)
{
    int n = knob1.size() + 1;
    TreeGraph g(n);
    for (int i = 0; i < n - 1; i++) {
        g.addEdge(knob1[i] - 1, knob2[i] - 1);
    }
    for (int i = 0; i < n; i++) {
        if (g.edge[i].size() > 3) {
            return 0;
        }
    }
    int lastdep = 0;
    while ((1 << (lastdep + 1)) - 1 <= n) {
        lastdep++;
    }
    int rem = n - (1 << lastdep) + 1;
    int rootcnt = 0;
    // Enumerate the root
    for (int i = 0; i < n; i++) {
        if (g.edge[i].size() <= 2) {
            g.BFSDist(i);
            std::vector<int> cntdist(n);
            for (int j = 0; j < n; j++) {
                cntdist[g.dist[j]]++;
            }
            bool ok = true;
            for (int j = 0; j < lastdep; j++) {
                if (cntdist[j] != (1 << j)) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                continue;
            }
            for (int j = 0; j < lastdep; j++) {
                std::vector<int> cnt(n);
                for (int k = 0; k < n; k++) {
                    if (g.dist[k] == lastdep) {
                        int x = k;
                        for (int p = 0; p < j; p++) {
                            x = g.fa[x];
                        }
                        cnt[x]++;
                    }
                }
                int s = 0;
                int t = 0;
                for (int k = 0; k < n; k++) {
                    if (cnt[k] == (1 << j)) {
                        s++;
                    } else if (cnt[k] > 0) {
                        t++;
                    }
                }
                if (s != (rem >> j) || t > 1) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                continue;
            }
            rootcnt++;
        }
    }
    long long ans = 1;
    for (int i = lastdep - 1; i >= 1; i--) {
        ans <<= (1 << (i - 1 + ((rem >> i) & 1))) - 1 + ((rem & ((1 << (i + 1)) - 1)) == 0);
    }
    return ans * rootcnt;
}
