#include <queue>
#include <utility>
#include <vector>

class TreeGraph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> fa;
    std::vector<int> order;

    TreeGraph() { }
    TreeGraph(int n_) : n(n_), edge(n), fa(n, -1) { }

    void addEdge(int x, int y);
    void BFS(int s);
};

void TreeGraph::addEdge(int x, int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}

void TreeGraph::BFS(int s)
{
    std::queue<int> que;
    que.push(s);
    fa[s] = -1;
    order.reserve(n);
    order.clear();
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        order.push_back(x);
        for (auto y : edge[x]) {
            if (y != fa[x]) {
                fa[y] = x;
                que.push(y);
            }
        }
    }
}

class CentaurCompany {
  public:
    double getvalue(std::vector<int> a, std::vector<int> b);
};

double CentaurCompany::getvalue(std::vector<int> a, std::vector<int> b)
{
    int n = a.size() + 1;
    TreeGraph g(n);
    for (int i = 0; i < n - 1; i++) {
        g.addEdge(a[i] - 1, b[i] - 1);
    }
    g.BFS(0);
    // f[i][j][k] = number of ways to choose nodes from subtree i and (2
    // * connected component count + number of unselected nodes) = j,
    // and k = whether node i is chosen
    std::vector<std::vector<std::pair<long long, long long>>> f(n, std::vector<std::pair<long long, long long>>(2 * n));
    for (int i = 0; i < n; i++) {
        f[i][1].first = 1;
        f[i][2].second = 1;
    }
    for (int i = n - 1; i >= 1; i--) {
        int x = g.order[i];
        int y = g.fa[x];
        std::vector<std::pair<long long, long long>> h(2 * n);
        // Merge f[x] into f[y]
        for (int j = 0; j < 2 * n; j++) {
            for (int k = 0; k < 2 * n - j; k++) {
                h[k + j].first += (long long)f[y][k].first * f[x][j].first;
                h[k + j].second += (long long)f[y][k].second * f[x][j].first;
                h[k + j].first += (long long)f[y][k].first * f[x][j].second;
                if (k >= 2) {
                    h[k + j - 2].second += (long long)f[y][k].second * f[x][j].second;
                }
            }
        }
        f[y] = std::move(h);
    }
    long long ans = 0;
    for (int i = n + 2; i < 2 * n; i++) {
        ans += (i - n - 2) * f[0][i].first;
        ans += (i - n - 2) * f[0][i].second;
    }
    return (double)ans / (1LL << (n - 1));
}
