#include <cstdlib>
#include <queue>
#include <string>
#include <vector>

static int powermod(int x, int y, int m)
{
    int s = 1;
    while (y) {
        if (y & 1) {
            s = (long long)s * x % m;
        }
        x = (long long)x * x % m;
        y >>= 1;
    }
    return s;
}

class Graph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<char> vis;

    Graph() { }
    Graph(int n_) : n(n_), edge(n), vis(n) { }

    void addEdge(int x, int y);
    int BFS(int s);
};

void Graph::addEdge(int x, int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}

int Graph::BFS(int s)
{
    std::queue<int> que;
    int cnt = 0;
    que.push(s);
    vis[s] = true;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        cnt++;
        for (auto y : edge[x]) {
            if (!vis[y]) {
                vis[y] = true;
                que.push(y);
            }
        }
    }
    return cnt;
}

class GooseInZooDivOne {
  public:
    int count(std::vector<std::string> field, int dist);

  private:
    static const int MOD = 1000000007;
};

int GooseInZooDivOne::count(std::vector<std::string> field, int dist)
{
    int n = field.size();
    int m = field[0].length();
    Graph g(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == 'v') {
                for (int p = i; p < n; p++) {
                    for (int q = p == i ? j + 1 : 0; q < m; q++) {
                        if (field[p][q] == 'v' && std::abs(i - p) + std::abs(j - q) <= dist) {
                            g.addEdge(i * m + j, p * m + q);
                        }
                    }
                }
            }
        }
    }
    int cnteven = 0;
    int cntodd = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == 'v' && !g.vis[i * m + j]) {
                int s = g.BFS(i * m + j);
                if (s % 2 == 0) {
                    cnteven++;
                } else {
                    cntodd++;
                }
            }
        }
    }
    // If there is at least one odd part, only half of the subsets are
    // legal
    return powermod(2, cnteven + cntodd - (cntodd > 0), MOD) - 1;
}
