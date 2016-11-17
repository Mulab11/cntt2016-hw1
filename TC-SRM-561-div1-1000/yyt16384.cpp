#include <queue>
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

class Orienteering {
  public:
    double expectedLength(std::vector<std::string> field, int K);
};

double Orienteering::expectedLength(std::vector<std::string> field, int K)
{
    int n = field.size();
    int m = field[0].length();
    std::vector<std::vector<int>> nodeid(n, std::vector<int>(m));
    int noden = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] != '#') {
                nodeid[i][j] = noden++;
            }
        }
    }
    TreeGraph g(noden);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] != '#') {
                if (j < m - 1 && field[i][j + 1] != '#') {
                    g.addEdge(nodeid[i][j], nodeid[i][j + 1]);
                }
                if (i < n - 1 && field[i + 1][j] != '#') {
                    g.addEdge(nodeid[i][j], nodeid[i + 1][j]);
                }
            }
        }
    }
    std::vector<int> specnodes;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == '*') {
                specnodes.push_back(nodeid[i][j]);
            }
        }
    }
    std::vector<std::vector<int>> dist;
    for (int i = 0; i < noden; i++) {
        g.BFSDist(i);
        dist.push_back(g.dist);
    }
    // pp[i] = probability to choose K nodes from i nodes
    std::vector<double> pp(specnodes.size() + 1);
    for (int i = 0; i <= (int)specnodes.size(); i++) {
        double p = 1;
        for (int j = 0; j < K; j++) {
            p *= i - j;
            p /= specnodes.size() - j;
        }
        pp[i] = p;
    }
    double ans = 0;
    g.BFSDist(0);
    for (int i = 1; i < noden; i++) {
        int cnt = 0;
        for (auto x : specnodes) {
            if (dist[x][i] < dist[x][g.fa[i]]) {
                cnt++;
            }
        }
        // This edge is counted if both sides have at lease one node
        // selected
        double p = 1 - pp[cnt] - pp[specnodes.size() - cnt];
        ans += 2 * p;
    }
    // Enumerate the pair of nodes with longest distance
    for (int i = 0; i < (int)specnodes.size(); i++) {
        for (int j = i + 1; j < (int)specnodes.size(); j++) {
            int x = specnodes[i];
            int y = specnodes[j];
            int cnt = 0;
            for (int k = 0; k < (int)specnodes.size(); k++) {
                int z = specnodes[k];
                if ((dist[x][z] < dist[x][y] || (dist[x][z] == dist[x][y] && z >= y)) && (dist[y][z] < dist[x][y] || (dist[y][z] == dist[x][y] && z >= x))) {
                    cnt++;
                }
            }
            double p = pp[cnt] - 2 * pp[cnt - 1] + pp[cnt - 2];
            ans -= p * dist[x][y];
        }
    }
    return ans;
}
