#include <string>
#include <utility>
#include <vector>

class TreeGraph {
  public:
    int n = 0;
    std::vector<std::vector<int>> edge;
    std::vector<int> fa;

    TreeGraph() { }
    TreeGraph(int n_) : n(n_), edge(n), fa(n, -1) { }
    TreeGraph(int n_, const std::vector<std::pair<int, int>> &e);

    void addEdge(int x, int y);
    int DFSGetAnswer(int x);
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

int TreeGraph::DFSGetAnswer(int x)
{
    int ans = 0;
    int cnt0 = 0;
    for (auto y : edge[x]) {
        if (y != fa[x]) {
            fa[y] = x;
            int u = DFSGetAnswer(y);
            ans += u;
            cnt0 += u == 0;
        }
    }
    // There are cnt0 subtrees with no beacons at all, and we need to
    // fill all but one of them
    if (cnt0 > 0) {
        ans += cnt0 - 1;
    }
    return ans;
}

class TPS {
  public:
    int minimalBeacons(std::vector<std::string> linked);
};

int TPS::minimalBeacons(std::vector<std::string> linked)
{
    int n = linked.size();
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (linked[i][j] == 'Y') {
                edges.push_back(std::make_pair(i, j));
            }
        }
    }
    TreeGraph g(n, edges);
    // Solution is legal <=> For every node, there can be at most one
    // subtree of this node that has no beacons
    // Choose a node with degree of at least 3 to simplify calculation.
    // In this case, the father edge of any non-root node is satisfied
    // because there is always another subtree of root that has beacons.
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (g.edge[i].size() >= 3) {
            root = i;
            break;
        }
    }
    if (root == -1) {
        return n > 1 ? 1 : 0;  // The tree is a chain
    }
    return g.DFSGetAnswer(root);
}
