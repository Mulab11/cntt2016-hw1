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

class GameInDarknessDiv1 {
  public:
    std::string check(std::vector<std::string> field);
};

std::string GameInDarknessDiv1::check(std::vector<std::string> field)
{
    int n = field.size();
    int m = field[0].length();
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (field[i][j] != '#' && field[i][j + 1] != '#') {
                edges.push_back(std::make_pair(i * m + j, i * m + j + 1));
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] != '#' && field[i + 1][j] != '#') {
                edges.push_back(std::make_pair(i * m + j, (i + 1) * m + j));
            }
        }
    }
    TreeGraph g(n * m, edges);
    int apos = -1;
    int bpos = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == 'A') {
                apos = i * m + j;
            }
            if (field[i][j] == 'B') {
                bpos = i * m + j;
            }
        }
    }
    g.BFSDist(apos);
    std::vector<int> dista = g.dist;
    g.BFSDist(bpos);
    std::vector<int> distb = g.dist;
    for (int i = 0; i < n * m; i++) {
        if (dista[i] >= distb[i] + 2 && g.edge[i].size() >= 3) {
            // Bob can reach this junction before Alice
            int cnt = 0;
            for (auto x : g.edge[i]) {
                bool ok = false;
                for (auto y : g.edge[x]) {
                    if (y != i && g.edge[y].size() >= 2) {
                        ok = true;
                        break;
                    }
                }
                if (ok) {
                    cnt++;  // This subtree has a depth of at least 3
                }
            }
            if (cnt >= 3) {
                // If there are 3 subtrees with depth of at least 3,
                // there are at least 2 subtrees available when Alice
                // approaches this junction. Bob can find out the first
                // subtree that Alice will go into for at least 2 turns,
                // then Bob can go into the other subtree and go back to
                // the junction when Alice goes away.
                return "Bob wins";
            }
        }
    }
    // If there are no such junctions, Alice can go towards Bob, and
    // when Alice hits a junction with dista[i] >= distb[i] + 2, Alice
    // can make sure that Bob is not in a subtree with depth of <= 2 by
    // getting into the subtree for one turn and then get back to the
    // junction. If there are still 2 subtrees remaining, the subtree
    // with Alice has a depth of 2, and dista[i] >= distb[i] + 2 holds
    // for every junction. So Alice can just go to the leaf node
    // farthest from the junction and the above analysis still holds,
    // while this situation will never appear again.
    return "Alice wins";
}
