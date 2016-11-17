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

class ArcadeManao {
  public:
    int shortestLadder(std::vector<std::string> level, int coinRow, int coinColumn);
};

int ArcadeManao::shortestLadder(std::vector<std::string> level, int coinRow, int coinColumn)
{
    int n = level.size();
    int m = level[0].length();
    Graph g(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (level[i][j] == 'X' && level[i][j + 1] == 'X') {
                g.addEdge(i * m + j, i * m + j + 1);
            }
        }
    }
    int len = 0;
    while (true) {
        g.BFSDist((coinRow - 1) * m + coinColumn - 1);
        bool ok = false;
        for (int i = 0; i < m; i++) {
            if (g.dist[(n - 1) * m + i] < INF) {
                ok = true;
                break;
            }
        }
        if (ok) {
            break;
        }
        // Try to increase ladder length by 1
        len++;
        for (int i = 0; i < n - len; i++) {
            for (int j = 0; j < m; j++) {
                if (level[i][j] == 'X' && level[i + len][j] == 'X') {
                    g.addEdge(i * m + j, (i + len) * m + j);
                }
            }
        }
    }
    return len;
}
