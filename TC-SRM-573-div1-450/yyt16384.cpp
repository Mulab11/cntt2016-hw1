#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

class DirectedGraph {
  public:
    int n = 0;
    std::vector<std::vector<std::pair<int, long long>>> edge;
    std::vector<long long> dist;

    DirectedGraph() { }
    DirectedGraph(int n_) : n(n_), edge(n), dist(n) { }

    void addEdge(int x, int y, long long w);
    void dijkstra();
};

void DirectedGraph::addEdge(int x, int y, long long w)
{
    edge[x].push_back(std::make_pair(y, w));
}

void DirectedGraph::dijkstra()
{
    std::vector<char> vis(n);
    for (int i = 0; i < n; i++) {
        int r = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && (r == -1 || dist[j] < dist[r])) {
                r = j;
            }
        }
        vis[r] = true;
        for (auto e : edge[r]) {
            dist[e.first] = std::min(dist[e.first], dist[r] + e.second);
        }
    }
}

class SkiResorts {
  public:
    long long minCost(std::vector<std::string> road, std::vector<int> altitude);
};

long long SkiResorts::minCost(std::vector<std::string> road, std::vector<int> altitude)
{
    int n = road.size();
    std::vector<int> r = altitude;
    std::sort(r.begin(), r.end());
    // f[i][j] = minimum cost of moving to node j and changing its
    // altitude to r[i]
    std::vector<std::vector<long long>> f(n, std::vector<long long>(n, INFLL));
    for (int i = 0; i < n; i++) {
        f[i][0] = std::abs(altitude[0] - r[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        // Previous node has higher altitude
        for (int j = 0; j < n; j++) {
            for (int p = i + 1; p < n; p++) {
                for (int q = 0; q < n; q++) {
                    if (road[j][q] == 'Y') {
                        f[i][j] = std::min(f[i][j], f[p][q] + std::abs(altitude[j] - r[i]));
                    }
                }
            }
        }
        // Previous node has the same altitude
        DirectedGraph g(n);
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < n; p++) {
                if (road[j][p] == 'Y') {
                    g.addEdge(j, p, std::abs(altitude[p] - r[i]));
                }
            }
        }
        g.dist = f[i];
        g.dijkstra();
        f[i] = g.dist;
    }
    long long ans = INFLL;
    for (int i = 0; i < n; i++) {
        ans = std::min(ans, f[i][n - 1]);
    }
    return ans == INFLL ? -1 : ans;
}
