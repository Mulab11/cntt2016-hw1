#include <algorithm>
#include <queue>
#include <string>
#include <vector>

static const int INF = 0x3f3f3f3f;

class Graph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> dist;

    Graph() { }
    Graph(int n_) : n(n_), edge(n), dist(n) { }

    void addEdge(int x, int y);
    void BFSDist(int s);
};

void Graph::addEdge(int x, int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}

void Graph::BFSDist(int s)
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

class Egalitarianism {
  public:
    int maxDifference(std::vector<std::string> isFriend, int d);
};

int Egalitarianism::maxDifference(std::vector<std::string> isFriend, int d)
{
    int n = isFriend.size();
    Graph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (isFriend[i][j] == 'Y') {
                g.addEdge(i, j);
            }
        }
    }
    g.BFSDist(0);
    for (int i = 0; i < n; i++) {
        if (g.dist[i] == INF) {
            return -1;
        }
    }
    int s = 0;
    for (int i = 0; i < n; i++) {
        // Assume node i has lowest weight
        g.BFSDist(i);
        for (int j = 0; j < n; j++) {
            s = std::max(s, g.dist[j]);
        }
    }
    return s * d;
}
