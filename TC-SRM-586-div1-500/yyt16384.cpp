#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class DirectedGraph {
  public:
    int n = 0;
    std::vector<std::vector<std::pair<int, int>>> edge;
    std::vector<std::vector<int>> dist;

    DirectedGraph() { }
    DirectedGraph(int n_) : n(n_), edge(n), dist(n, std::vector<int>(n, INF)) { }

    void addEdge(int x, int y, int w);
    void floyd();
};

void DirectedGraph::addEdge(int x, int y, int w)
{
    edge[x].push_back(std::make_pair(y, w));
}

void DirectedGraph::floyd()
{
    for (int i = 0; i < n; i++) {
        for (auto x : edge[i]) {
            dist[i][x.first] = std::min(dist[i][x.first], x.second);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

class History {
  public:
    std::string verifyClaims(std::vector<std::string> dynasties, std::vector<std::string> battles, std::vector<std::string> queries);
};

std::string History::verifyClaims(std::vector<std::string> dynasties, std::vector<std::string> battles, std::vector<std::string> queries)
{
    std::string battlestr;
    for (const auto &x : battles) {
        battlestr += x;
    }
    std::vector<std::vector<int>> d(dynasties.size());
    for (int i = 0; i < (int)dynasties.size(); i++) {
        std::istringstream ss(dynasties[i]);
        int x;
        while (ss >> x) {
            d[i].push_back(x);
        }
    }
    DirectedGraph g(dynasties.size());
    for (int i = 0; i < (int)battlestr.length(); i += 6) {
        int u1 = battlestr[i] - 'A';
        int v1 = battlestr[i + 1] - '0';
        int u2 = battlestr[i + 3] - 'A';
        int v2 = battlestr[i + 4] - '0';
        // The two intervals must intersect
        int d21 = d[u2][v2 + 1] - d[u1][v1] - 1;
        int d12 = d[u1][v1 + 1] - d[u2][v2] - 1;
        g.addEdge(u2, u1, d21);
        g.addEdge(u1, u2, d12);
    }
    g.floyd();
    std::string ans;
    for (const auto &x : queries) {
        int u1 = x[0] - 'A';
        int v1 = x[1] - '0';
        int u2 = x[3] - 'A';
        int v2 = x[4] - '0';
        // Battle is possible if there are no negative cycles after
        // adding these edges
        int d21 = d[u2][v2 + 1] - d[u1][v1] - 1;
        int d12 = d[u1][v1 + 1] - d[u2][v2] - 1;
        if (g.dist[u1][u2] + d21 >= 0 && g.dist[u2][u1] + d12 >= 0) {
            ans += 'Y';
        } else {
            ans += 'N';
        }
    }
    return ans;
}
