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
    void dijkstra();
};

void DirectedGraph::addEdge(int x, int y, int w)
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

class FoxTheLinguist {
  public:
    int minimalHours(int n, std::vector<std::string> courseInfo);

  private:
    static const int CNT = 10;
};

int FoxTheLinguist::minimalHours(int n, std::vector<std::string> courseInfo)
{
    std::string s;
    for (const auto &x : courseInfo) {
        s += x;
    }
    DirectedGraph g(n * CNT + 1);
    for (int i = 0; i < (int)s.length(); i += 12) {
        int u1 = s[i] - 'A';
        int v1 = s[i + 1] - '0';
        int u2 = s[i + 4] - 'A';
        int v2 = s[i + 5] - '0';
        int w = std::stoi(s.substr(i + 7, 4));
        g.addEdge(u2 * CNT + v2, u1 * CNT + v1, w);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < CNT - 1; j++) {
            g.addEdge(i * CNT + j, i * CNT + j + 1, 0);
        }
        g.addEdge(i * CNT, n * CNT, 0);
    }
    // f[i][j] = minimum cost of mastering set i starting from node j
    std::vector<std::vector<int>> f(1 << n, std::vector<int>(n * CNT + 1, INF));
    for (int i = 0; i < n; i++) {
        f[1 << i][i * CNT + CNT - 1] = 0;
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j <= n * CNT; j++) {
            for (auto e : g.edge[j]) {
                int k = e.first;
                int w = e.second;
                // Merge node j into node k
                for (int p = i & (i - 1); p != 0; p = (p - 1) & i) {
                    int q = i & ~p;
                    f[i][k] = std::min(f[i][k], f[p][k] + f[q][j] + w);
                }
            }
        }
        // Solve current layer, use Dijkstra to deal with cycles
        g.dist = f[i];
        g.dijkstra();
        f[i] = g.dist;
    }
    int ans = f[(1 << n) - 1][n * CNT];
    return ans >= INF ? -1 : ans;
}
