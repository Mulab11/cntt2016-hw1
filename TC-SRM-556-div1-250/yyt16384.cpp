#include <queue>
#include <string>
#include <utility>
#include <vector>

class Graph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<char> vis;

    Graph() { }
    Graph(int n_) : n(n_), edge(n), vis(n) { }

    void addEdge(int x, int y);
    void BFS(int s);
};

void Graph::addEdge(int x, int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}

void Graph::BFS(int s)
{
    std::queue<int> que;
    que.push(s);
    vis[s] = true;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto y : edge[x]) {
            if (!vis[y]) {
                vis[y] = true;
                que.push(y);
            }
        }
    }
}

class XorTravelingSalesman {
  public:
    int maxProfit(std::vector<int> cityValues, std::vector<std::string> roads);

  private:
    static const int MAXBITS = 10;

    std::vector<int> gaussianElimination(std::vector<int> f);
};

int XorTravelingSalesman::maxProfit(std::vector<int> cityValues, std::vector<std::string> roads)
{
    int n = cityValues.size();
    Graph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (roads[i][j] == 'Y') {
                g.addEdge(i, j);
            }
        }
    }
    g.BFS(0);
    std::vector<int> c;
    // Moving from a to b and then back to a will xor w[a]^w[b] to
    // answer, and moving from a node to any adjacent node changes the
    // parity of items in answer, so every combination is possible
    for (int i = 0; i < n; i++) {
        if (g.vis[i]) {
            c.push_back(cityValues[i]);
        }
    }
    std::vector<int> f = gaussianElimination(c);
    int ans = 0;
    for (auto x : f) {
        if (!x) {
            break;
        }
        ans ^= x;
    }
    return ans;
}

std::vector<int> XorTravelingSalesman::gaussianElimination(std::vector<int> f)
{
    int cur = 0;
    for (int i = MAXBITS - 1; i >= 0; i--) {
        int r = -1;
        for (int j = cur; j < (int)f.size(); j++) {
            if ((f[j] >> i) & 1) {
                r = j;
                break;
            }
        }
        if (r == -1) {
            continue;
        }
        std::swap(f[cur], f[r]);
        for (int j = 0; j < (int)f.size(); j++) {
            if (j != cur && ((f[j] >> i) & 1)) {
                f[j] ^= f[cur];
            }
        }
        cur++;
    }
    return f;
}
