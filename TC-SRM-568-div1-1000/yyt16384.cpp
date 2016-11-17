#include <algorithm>
#include <queue>
#include <string>
#include <utility>
#include <vector>

class Graph {
  public:
    int n = 0;
    std::vector<std::vector<std::pair<int, bool>>> edge;
    std::vector<int> color;

    Graph() { }
    Graph(int n_) : n(n_), edge(n), color(n) { }

    void addEdge(int x, int y, bool col);
    bool isColorable();

  private:
    bool BFSColor(int s);
};

void Graph::addEdge(int x, int y, bool col)
{
    edge[x].push_back(std::make_pair(y, col));
    edge[y].push_back(std::make_pair(x, col));
}

bool Graph::isColorable()
{
    std::fill(color.begin(), color.end(), -1);
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!BFSColor(i)) {
                return false;
            }
        }
    }
    return true;
}

bool Graph::BFSColor(int s)
{
    std::queue<int> que;
    que.push(s);
    color[s] = 0;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto e : edge[x]) {
            if (color[e.first] == -1) {
                color[e.first] = color[x] ^ e.second;
                que.push(e.first);
            } else if (color[e.first] != (color[x] ^ e.second)) {
                return false;
            }
        }
    }
    return true;
}

class DisjointSemicircles {
  public:
    std::string getPossibility(std::vector<int> labels);

  private:
    std::string getPossibility1(const std::vector<int> &labels);
    std::string getPossibility2(const std::vector<int> &labels);
};

std::string DisjointSemicircles::getPossibility(std::vector<int> labels)
{
    int cntempty = 0;
    for (auto x : labels) {
        if (x == -1) {
            cntempty++;
        }
    }
    if (cntempty <= 12) {
        return getPossibility1(labels);
    } else {
        return getPossibility2(labels);
    }
}

std::string DisjointSemicircles::getPossibility1(const std::vector<int> &labels)
{
    int n = labels.size();
    std::vector<std::pair<int, int>> matches;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (labels[i] != -1 && labels[i] == labels[j]) {
                matches.push_back(std::make_pair(i, j));
            }
        }
    }
    std::vector<int> emptypos;
    for (int i = 0; i < n; i++) {
        if (labels[i] == -1) {
            emptypos.push_back(i);
        }
    }
    int ss = 1;
    for (int i = emptypos.size() - 1; i >= 1; i -= 2) {
        ss *= i;
    }
    // Enumerate the pairing of the remaining positions
    for (int i = 0; i < ss; i++) {
        int u = i;
        std::vector<char> vis(emptypos.size());
        std::vector<std::pair<int, int>> c = matches;
        for (int j = 0; j < (int)emptypos.size() / 2; j++) {
            int s = 0;
            while (vis[s]) {
                s++;
            }
            int t = s;
            int r = u % (emptypos.size() - 2 * j - 1);
            for (int k = 0; k <= r; k++) {
                t++;
                while (vis[t]) {
                    t++;
                }
            }
            vis[s] = true;
            vis[t] = true;
            c.push_back(std::make_pair(emptypos[s], emptypos[t]));
            u /= emptypos.size() - 2 * j - 1;
        }
        Graph g(c.size());
        // Intersecting pairs can't be in the same part
        for (int j = 0; j < (int)c.size(); j++) {
            for (int k = 0; k < (int)c.size(); k++) {
                if (c[j].first < c[k].first && c[k].first < c[j].second && c[j].second < c[k].second) {
                    g.addEdge(j, k, true);
                }
            }
        }
        if (g.isColorable()) {
            return "POSSIBLE";
        }
    }
    return "IMPOSSIBLE";
}

std::string DisjointSemicircles::getPossibility2(const std::vector<int> &labels)
{
    int n = labels.size();
    std::vector<std::pair<int, int>> matches;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (labels[i] != -1 && labels[i] == labels[j]) {
                matches.push_back(std::make_pair(i, j));
            }
        }
    }
    std::vector<int> sumfree(n + 1);
    for (int i = 0; i < n; i++) {
        sumfree[i + 1] = sumfree[i] + (labels[i] == -1);
    }
    // Enumerate whether to put each pair up or down
    for (int i = 0; i < (1 << matches.size()); i++) {
        bool ok = true;
        for (int j = 0; j < (int)matches.size(); j++) {
            for (int k = 0; k < (int)matches.size(); k++) {
                if (matches[j].first < matches[k].first && matches[k].first < matches[j].second && matches[j].second < matches[k].second && ((i >> j) & 1) == ((i >> k) & 1)) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                break;
            }
        }
        if (!ok) {
            continue;
        }
        Graph g(n + 1);
        // Total number of points in the up part must be even
        g.addEdge(0, n, false);
        for (int j = 0; j < (int)matches.size(); j++) {
            int l = matches[j].first;
            int r = matches[j].second;
            // Point l and r are already decided
            g.addEdge(l, l + 1, false);
            g.addEdge(r, r + 1, false);
            // Parity in the interval is required
            bool col = ((i >> j) & 1) ? (sumfree[r] - sumfree[l + 1]) % 2 : false;
            g.addEdge(l + 1, r, col);
        }
        if (g.isColorable()) {
            return "POSSIBLE";
        }
    }
    return "IMPOSSIBLE";
}
