#include <algorithm>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class FlowGraph {
  public:
    int n = 0;
    int s = -1;
    int t = -1;
    std::vector<std::vector<std::tuple<int, int, int, int>>> edge;

    FlowGraph() { }
    FlowGraph(int n_, int s_, int t_) : n(n_), s(s_), t(t_), edge(n) { }

    void addEdge(int x, int y, int w, int c);
    std::pair<int, int> minCostMaxFlow();

  private:
    std::vector<int> dist;
    std::vector<int> pre;

    void getDist();
    std::pair<int, int> augment();
};

void FlowGraph::addEdge(int x, int y, int w, int c)
{
    int idx = edge[x].size();
    int idy = edge[y].size();
    edge[x].push_back(std::make_tuple(y, w, c, idy));
    edge[y].push_back(std::make_tuple(x, 0, -c, idx));
}

std::pair<int, int> FlowGraph::minCostMaxFlow()
{
    dist.resize(n);
    pre.resize(n);
    int flow = 0;
    int cost = 0;
    while (true) {
        getDist();
        if (dist[t] == INF) {
            break;
        }
        std::pair<int, int> w = augment();
        flow += w.first;
        cost += w.second;
    }
    return std::make_pair(flow, cost);
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

std::pair<int, int> FlowGraph::augment()
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
    return std::make_pair(flow, flow * dist[t]);
}

class CurvyonRails {
  public:
    int getmin(std::vector<std::string> field);
};

int CurvyonRails::getmin(std::vector<std::string> field)
{
    int n = field.size();
    int m = field[0].length();
    FlowGraph g(3 * n * m + 2, 3 * n * m, 3 * n * m + 1);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] != 'w') {
                cnt++;
                // Each town connects with two roads, and connecting to
                // two horizontal or two vertical roads requires 1 cost
                // if current cell is 'C'
                if ((i + j) % 2 == 0) {
                    g.addEdge(g.s, i * m + j, 2, 0);
                    g.addEdge(i * m + j, i * m + j + n * m, 1, 0);
                    g.addEdge(i * m + j, i * m + j + n * m, 1, field[i][j] == 'C');
                    g.addEdge(i * m + j, i * m + j + 2 * n * m, 1, 0);
                    g.addEdge(i * m + j, i * m + j + 2 * n * m, 1, field[i][j] == 'C');
                    if (j < m - 1 && field[i][j + 1] != 'w') {
                        g.addEdge(i * m + j + n * m, i * m + j + 1 + n * m, 1, 0);
                    }
                    if (i < n - 1 && field[i + 1][j] != 'w') {
                        g.addEdge(i * m + j + 2 * n * m, (i + 1) * m + j + 2 * n * m, 1, 0);
                    }
                } else {
                    g.addEdge(i * m + j, g.t, 2, 0);
                    g.addEdge(i * m + j + n * m, i * m + j, 1, 0);
                    g.addEdge(i * m + j + n * m, i * m + j, 1, field[i][j] == 'C');
                    g.addEdge(i * m + j + 2 * n * m, i * m + j, 1, 0);
                    g.addEdge(i * m + j + 2 * n * m, i * m + j, 1, field[i][j] == 'C');
                    if (j < m - 1 && field[i][j + 1] != 'w') {
                        g.addEdge(i * m + j + 1 + n * m, i * m + j + n * m, 1, 0);
                    }
                    if (i < n - 1 && field[i + 1][j] != 'w') {
                        g.addEdge((i + 1) * m + j + 2 * n * m, i * m + j + 2 * n * m, 1, 0);
                    }
                }
            }
        }
    }
    std::pair<int, int> s = g.minCostMaxFlow();
    if (s.first < cnt) {
        return -1;
    } else {
        return s.second;
    }
}
