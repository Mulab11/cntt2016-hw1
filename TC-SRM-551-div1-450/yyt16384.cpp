#include <algorithm>
#include <string>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class DirectedGraph {
  public:
    int n = 0;
    std::vector<std::vector<std::pair<int, int>>> edge;
    std::vector<int> dist;

    DirectedGraph() { }
    DirectedGraph(int n_) : n(n_), edge(n), dist(n) { }

    void addEdge(int x, int y, int w);
    void dijkstra(int s);
};

void DirectedGraph::addEdge(int x, int y, int w)
{
    edge[x].push_back(std::make_pair(y, w));
}

void DirectedGraph::dijkstra(int s)
{
    std::fill(dist.begin(), dist.end(), INF);
    dist[s] = 0;
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

class ColorfulWolves {
  public:
    int getmin(std::vector<std::string> colormap);
};

int ColorfulWolves::getmin(std::vector<std::string> colormap)
{
    int n = colormap.size();
    DirectedGraph g(n);
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (colormap[i][j] == 'Y') {
                // Moving from color i to color j requires removing all
                // previous edges
                g.addEdge(i, j, cnt);
                cnt++;
            }
        }
    }
    g.dijkstra(0);
    return g.dist[n - 1] == INF ? -1 : g.dist[n - 1];
}
