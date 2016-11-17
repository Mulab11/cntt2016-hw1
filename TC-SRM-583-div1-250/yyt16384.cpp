#include <algorithm>
#include <queue>
#include <vector>

static const int INF = 0x3f3f3f3f;

class DirectedGraph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> dist;

    DirectedGraph() { }
    DirectedGraph(int n_) : n(n_), edge(n), dist(n) { }

    void addEdge(int x, int y);
    void BFSDist(int s);
};

void DirectedGraph::addEdge(int x, int y)
{
    edge[x].push_back(y);
}

void DirectedGraph::BFSDist(int s)
{
    std::queue<int> que;
    que.push(s);
    std::fill(dist.begin(), dist.end(), INF);
    dist[s] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto y : edge[x]) {
            if (dist[y] == INF) {
                dist[y] = dist[x] + 1;
                que.push(y);
            }
        }
    }
}

class TravelOnMars {
  public:
    int minTimes(std::vector<int> range, int startCity, int endCity);
};

int TravelOnMars::minTimes(std::vector<int> range, int startCity, int endCity)
{
    int n = range.size();
    DirectedGraph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((j - i + n) % n <= range[i] || (i - j + n) % n <= range[i]) {
                // Node j can be reached from node i
                g.addEdge(i, j);
            }
        }
    }
    g.BFSDist(startCity);
    return g.dist[endCity];
}
