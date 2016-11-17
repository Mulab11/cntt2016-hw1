#include <algorithm>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class FlowGraph {
  public:
    int n = 0;
    int s = -1;
    int t = -1;
    std::vector<std::vector<std::tuple<int, int, int>>> edge;

    FlowGraph() { }
    FlowGraph(int n_, int s_, int t_) : n(n_), s(s_), t(t_), edge(n) { }

    void addEdge(int x, int y, int w);
    int maxFlow();

  private:
    std::vector<int> dist;
    std::vector<int> curedge;

    void BFSDist();
    int DFSFlow(int x, int pre);
};

void FlowGraph::addEdge(int x, int y, int w)
{
    int idx = edge[x].size();
    int idy = edge[y].size();
    edge[x].push_back(std::make_tuple(y, w, idy));
    edge[y].push_back(std::make_tuple(x, 0, idx));
}

int FlowGraph::maxFlow()
{
    dist.resize(n);
    curedge.resize(n);
    int flow = 0;
    while (true) {
        BFSDist();
        if (dist[s] == INF) {
            break;
        }
        std::fill(curedge.begin(), curedge.end(), 0);
        flow += DFSFlow(s, INF);
    }
    return flow;
}

void FlowGraph::BFSDist()
{
    std::queue<int> que;
    que.push(t);
    std::fill(dist.begin(), dist.end(), INF);
    dist[t] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto e : edge[x]) {
            int y = std::get<0>(e);
            if (dist[y] == INF && std::get<1>(edge[y][std::get<2>(e)])) {
                dist[y] = dist[x] + 1;
                que.push(y);
            }
        }
    }
}

int FlowGraph::DFSFlow(int x, int pre)
{
    if (x == t) {
        return pre;
    }
    int sum = 0;
    for (int &i = curedge[x]; i < (int)edge[x].size(); i++) {
        auto &e = edge[x][i];
        int y = std::get<0>(e);
        int w = std::get<1>(e);
        if (w && dist[x] == dist[y] + 1) {
            int u = std::min(pre, w);
            int v = DFSFlow(y, u);
            sum += v;
            pre -= v;
            std::get<1>(e) -= v;
            std::get<1>(edge[y][std::get<2>(e)]) += v;
            if (!pre) {
                break;
            }
        }
    }
    return sum;
}

class CosmicBlocks {
  public:
    int getNumOrders(std::vector<int> blockTypes, int minWays, int maxWays);

  private:
    std::vector<int> badedges;
    std::vector<std::vector<std::pair<int, int>>> trans;

    void initOrders(int n);
    void initTrans(const std::vector<int> &a);
    int searchGraph(int ss, int cur, int edges, int n, int minlim, int maxlim);
    bool checkGraph(int edges, int minlim, int maxlim);
};

int CosmicBlocks::getNumOrders(std::vector<int> blockTypes, int minWays, int maxWays)
{
    initOrders(blockTypes.size());
    initTrans(blockTypes);
    int ans = 0;
    for (int i = 0; i < (1 << blockTypes.size()); i++) {
        ans += searchGraph(i, i, 0, blockTypes.size(), minWays, maxWays);
    }
    return ans;
}

void CosmicBlocks::initOrders(int n)
{
    int s = 1;
    for (int i = 1; i <= n; i++) {
        s *= i;
    }
    badedges.resize(s);
    // Enumerate the order of block removal
    for (int i = 0; i < s; i++) {
        std::vector<int> rem(n);
        for (int j = 0; j < n; j++) {
            rem[j] = j;
        }
        std::vector<int> seq(n);
        int t = i;
        for (int j = 0; j < n; j++) {
            int idx = t % (n - j);
            t /= n - j;
            seq[j] = rem[idx];
            rem.erase(rem.begin() + idx);
        }
        int es = 0;
        for (int j = 0; j < n; j++) {
            int x = seq[j];
            for (int k = 0; k < j; k++) {
                int y = seq[k];
                es |= 1 << (x * (n - 1) + y - (y > x));
            }
        }
        badedges[i] = es;
    }
}

void CosmicBlocks::initTrans(const std::vector<int> &a)
{
    int n = a.size();
    trans.clear();
    trans.resize(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        std::vector<int> c1;
        std::vector<int> c0;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                c1.push_back(j);
            } else {
                c0.push_back(j);
            }
        }
        // Enumerate the edges between the current layer and the next
        // layer
        for (int j = 0; j < (1 << (c1.size() * c0.size())); j++) {
            int ss = 0;
            FlowGraph g(n + 2, n, n + 1);
            std::vector<int> cnt(n);
            for (int k = 0; k < (int)c1.size(); k++) {
                int x = c1[k];
                for (int p = 0; p < (int)c0.size(); p++) {
                    int y = c0[p];
                    if ((j >> (k * c0.size() + p)) & 1) {
                        ss |= 1 << (x * (n - 1) + y - (y > x));
                        cnt[x]++;
                        cnt[y]++;
                        g.addEdge(x, y, INF);
                    }
                }
            }
            bool ok = true;
            for (int k = 0; k < n; k++) {
                if (cnt[k] > a[k]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                continue;
            }
            int sum = 0;
            for (auto x : c1) {
                g.addEdge(g.s, x, a[x] - cnt[x]);
            }
            int nexti = 0;
            for (auto x : c0) {
                if (cnt[x]) {
                    nexti |= 1 << x;
                    g.addEdge(x, g.t, a[x] - cnt[x]);
                    sum += a[x] - cnt[x];
                }
            }
            int flow = g.maxFlow();
            if (flow < sum) {
                continue;
            }
            if (nexti) {
                trans[i].push_back(std::make_pair(ss, nexti));
            }
        }
    }
}

int CosmicBlocks::searchGraph(int ss, int cur, int edges, int n, int minlim, int maxlim)
{
    if (ss == (1 << n) - 1) {
        return checkGraph(edges, minlim, maxlim);
    }
    int ans = 0;
    for (auto x : trans[cur]) {
        if (!(ss & x.second)) {
            ans += searchGraph(ss | x.second, x.second, edges | x.first, n, minlim, maxlim);
        }
    }
    return ans;
}

bool CosmicBlocks::checkGraph(int edges, int minlim, int maxlim)
{
    int s = 0;
    for (auto x : badedges) {
        if (!(edges & x)) {
            s++;
        }
    }
    return s >= minlim && s <= maxlim;
}
