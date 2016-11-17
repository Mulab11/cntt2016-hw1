#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class Graph {
  public:
    int n = 0;
    std::vector<std::vector<std::pair<int, int>>> edge;
    std::vector<std::vector<int>> dist;

    Graph() { }
    Graph(int n_) : n(n_), edge(n), dist(n, std::vector<int>(n, INF)) { }

    void addEdge(int x, int y, int w);
    void floyd();
};

void Graph::addEdge(int x, int y, int w)
{
    edge[x].push_back(std::make_pair(y, w));
    edge[y].push_back(std::make_pair(x, w));
}

void Graph::floyd()
{
    for (int i = 0; i < n; i++) {
        for (auto x : edge[i]) {
            dist[i][x.first] = std::min(dist[i][x.first], x.second);
        }
    }
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

class TravellingPurchasingMan {
  public:
    int maxStores(int N, std::vector<std::string> interestingStores, std::vector<std::string> roads);
};

int TravellingPurchasingMan::maxStores(int N, std::vector<std::string> interestingStores, std::vector<std::string> roads)
{
    Graph g(N);
    for (const auto &x : roads) {
        std::istringstream ss(x);
        int u, v, w;
        ss >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    g.floyd();
    int m = interestingStores.size();
    std::vector<int> opentime(m);
    std::vector<int> closetime(m);
    std::vector<int> duration(m);
    for (int i = 0; i < m; i++) {
        std::istringstream ss(interestingStores[i]);
        ss >> opentime[i] >> closetime[i] >> duration[i];
    }
    // f[i][j] = minimum ending time after purchasing at stores in set i
    // and ending at store j
    std::vector<std::vector<int>> f(1 << m, std::vector<int>(m, INF));
    for (int i = 0; i < m; i++) {
        f[0][i] = g.dist[N - 1][i];
    }
    for (int i = 0; i < (1 << m); i++) {
        // Go between stores
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                f[i][k] = std::min(f[i][k], f[i][j] + g.dist[j][k]);
            }
        }
        for (int j = 0; j < m; j++) {
            if (!((i >> j) & 1) && f[i][j] <= closetime[j]) {
                // Purchase at store j
                int t = std::max(f[i][j], opentime[j]) + duration[j];
                f[i | (1 << j)][j] = std::min(f[i | (1 << j)][j], t);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << m); i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            if ((i >> j) & 1) {
                cnt++;
            }
        }
        for (int j = 0; j < m; j++) {
            if (f[i][j] < INF) {
                ans = std::max(ans, cnt);
            }
        }
    }
    return ans;
}
