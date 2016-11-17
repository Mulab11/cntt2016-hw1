#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class TreeGraph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> fa;
    std::vector<int> dist;

    TreeGraph() { }
    TreeGraph(int n_) : n(n_), edge(n), fa(n, -1), dist(n) { }
    TreeGraph(int n_, const std::vector<std::pair<int, int>> &e);

    void addEdge(int x, int y);
    void BFSDist(int s);
};

TreeGraph::TreeGraph(int n_, const std::vector<std::pair<int, int>> &e) : TreeGraph(n_)
{
    for (auto x : e) {
        addEdge(x.first, x.second);
    }
}

void TreeGraph::addEdge(int x, int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}

void TreeGraph::BFSDist(int s)
{
    std::queue<int> que;
    que.push(s);
    fa[s] = -1;
    dist[s] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto y : edge[x]) {
            if (y != fa[x]) {
                fa[y] = x;
                dist[y] = dist[x] + 1;
                que.push(y);
            }
        }
    }
}

class TreeUnion {
  public:
    double expectedCycles(std::vector<std::string> tree1, std::vector<std::string> tree2, int K);
};

double TreeUnion::expectedCycles(std::vector<std::string> tree1, std::vector<std::string> tree2, int K)
{
    std::string s1;
    for (const auto &x : tree1) {
        s1 += x;
    }
    std::string s2;
    for (const auto &x : tree2) {
        s2 += x;
    }
    int val;
    std::vector<int> fa1;
    std::istringstream ss1(s1);
    while (ss1 >> val) {
        fa1.push_back(val);
    }
    std::vector<int> fa2;
    std::istringstream ss2(s2);
    while (ss2 >> val) {
        fa2.push_back(val);
    }
    int n = fa1.size() + 1;
    TreeGraph g1(n);
    TreeGraph g2(n);
    for (int i = 1; i < n; i++) {
        g1.addEdge(fa1[i - 1], i);
    }
    for (int i = 1; i < n; i++) {
        g2.addEdge(fa2[i - 1], i);
    }
    std::vector<int> dcnt1(K - 3);
    std::vector<int> dcnt2(K - 3);
    for (int i = 0; i < n; i++) {
        g1.BFSDist(i);
        for (int j = i + 1; j < n; j++) {
            if (g1.dist[j] <= K - 3) {
                dcnt1[g1.dist[j] - 1]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        g2.BFSDist(i);
        for (int j = i + 1; j < n; j++) {
            if (g2.dist[j] <= K - 3) {
                dcnt2[g2.dist[j] - 1]++;
            }
        }
    }
    // If k <= 7, the cycle must contain exactly 2 edges between the two
    // trees, so enumerate the length in each tree
    long long ans = 0;
    for (int i = 0; i < K - 3; i++) {
        int x = dcnt1[i];
        int y = dcnt2[K - 4 - i];
        // Two paths can be connected normally or reversed
        ans += (long long)x * y * 2;
    }
    // For each way to connect two paths, two elements in the
    // permutation must be fixed
    return (double)ans / n / (n - 1);
}
