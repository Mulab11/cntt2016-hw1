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

class GearsDiv1 {
  public:
    int getmin(std::string color, std::vector<std::string> graph);

  private:
    int getminBetween(std::string color, std::vector<std::string> graph, char col1, char col2);
};

int GearsDiv1::getmin(std::string color, std::vector<std::string> graph)
{
    int ansrg = getminBetween(color, graph, 'R', 'G');
    int ansrb = getminBetween(color, graph, 'R', 'B');
    int ansgb = getminBetween(color, graph, 'G', 'B');
    return std::min({ansrg, ansrb, ansgb});
}

int GearsDiv1::getminBetween(std::string color, std::vector<std::string> graph, char col1, char col2)
{
    // Get minimum number of removed nodes required to remove all edges
    // between col1 and col2
    int n = color.size();
    FlowGraph g(n + 2, n, n + 1);
    for (int i = 0; i < n; i++) {
        if (color[i] == col1) {
            g.addEdge(g.s, i, 1);
        }
        if (color[i] == col2) {
            g.addEdge(i, g.t, 1);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 'Y' && color[i] == col1 && color[j] == col2) {
                g.addEdge(i, j, 1);
            }
        }
    }
    return g.maxFlow();
}
