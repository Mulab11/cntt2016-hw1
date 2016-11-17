#include <algorithm>
#include <queue>
#include <string>
#include <tuple>
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
    void addEdgeBidirectional(int x, int y, int w);
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

void FlowGraph::addEdgeBidirectional(int x, int y, int w)
{
    int idx = edge[x].size();
    int idy = edge[y].size();
    edge[x].push_back(std::make_tuple(y, w, idy));
    edge[y].push_back(std::make_tuple(x, w, idx));
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

class OldBridges {
  public:
    std::string isPossible(std::vector<std::string> bridges, int a1, int a2, int an, int b1, int b2, int bn);
};

std::string OldBridges::isPossible(std::vector<std::string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
{
    int n = bridges.size();
    FlowGraph g(n + 2, n, n + 1);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bridges[i][j] != 'X') {
                g.addEdgeBidirectional(i, j, bridges[i][j] == 'O' ? 1 : INF);
            }
        }
    }
    FlowGraph g1 = g;
    g1.addEdge(g1.s, a1, an);
    g1.addEdge(a2, g1.t, an);
    g1.addEdge(g1.s, b1, bn);
    g1.addEdge(b2, g1.t, bn);
    FlowGraph g2 = g;
    g2.addEdge(g2.s, a1, an);
    g2.addEdge(a2, g2.t, an);
    g2.addEdge(g2.s, b2, bn);
    g2.addEdge(b1, g2.t, bn);
    if (g1.maxFlow() == an + bn && g2.maxFlow() == an + bn) {
        // The sum of two flows is a flow from a1 to a2, and the
        // difference of two flows is a flow from b1 to b2
        return "Yes";
    } else {
        return "No";
    }
}
